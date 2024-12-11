#include "ThreadsManager.h"

namespace ThreadsManager {

    std::atomic<bool> *add_thread(GROUP *group, std::thread *thr, int id_thr){
        group->count++;
        group->ids[group->count] = id_thr;
        // Memory allocation, this way variable isn't local only, and address returned by "new" assigned to a pointer.
        std::atomic<bool> *stop = new std::atomic<bool>{false};
        group->stops[group->count] = stop;
        group->handles[group->count] = thr;
        return stop;
    }

    std::thread *get_thread(GROUP *group, int id_thr){
        int pos = get_thread_pos(group, id_thr);
        return (pos != -0x1 && group->handles[pos] != nullptr) ? get_thread_by_pos(group, pos) : nullptr;
    }

    void remove_thread(GROUP *group, int id_thr){
        int pos = get_thread_pos(group, id_thr);
        if(pos != -0x1){
            remove_thread_by_pos(group, pos);
        }
    }

    bool stop_and_remove_thread(GROUP *group, int id_thr){
        int pos = get_thread_pos(group, id_thr);
        if(pos != -0x1){
            std::atomic<bool> *stop = get_stop_by_pos(group, pos);
            if(stop != nullptr){
                *stop = true;
                remove_thread_by_pos(group, pos);
                return true;
            }
        }
        return false;
    }

    // Anonymous Namespace, it's like make this members private.
    namespace {
        int get_thread_pos(ThreadsManager::GROUP *group, int id_thr){
            if(group->count > 0x0){
                for(int i = 0x0; i < group->count; i++){
                    if(group->ids[i] == id_thr && group->handles[i] != nullptr){
                        return i;
                    }
                }
            }
            return -0x1;
        }

        std::thread *get_thread_by_pos(ThreadsManager::GROUP *group, int pos){
            return reinterpret_cast<std::thread*>(group->handles[pos]);
        }

        std::atomic<bool> *get_stop_by_pos(ThreadsManager::GROUP *group, int pos){
            return reinterpret_cast<std::atomic<bool>*>(group->stops[pos]);
        }

        void remove_thread_by_pos(ThreadsManager::GROUP *group, int pos){
            group->count--;
            delete (std::atomic<bool>*) group->stops[pos];
            group->stops[pos] = nullptr;
            group->handles[pos] = nullptr;
            group->ids[pos] = -0x1;
        }
    }
}
