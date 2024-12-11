#include <thread>
#include <atomic>

#define MAX_NUM_THREADS 20

typedef void *HANDLE;

namespace ThreadsManager {
    
    typedef struct {
        int count;
        int ids[MAX_NUM_THREADS];
        HANDLE stops[MAX_NUM_THREADS];
        HANDLE handles[MAX_NUM_THREADS];
    } GROUP;

    std::atomic<bool> *add_thread(GROUP *group, std::thread *thr, int id_thr);

    std::thread *get_thread(GROUP *group, int id_thr);

    void remove_thread(GROUP *group, int id_thr);

    bool stop_and_remove_thread(GROUP *group, int id_thr);

    // Anonymous Namespace, it's like make this members private.
    namespace {
        int get_thread_pos(ThreadsManager::GROUP *group, int id_thr);

        std::thread *get_thread_by_pos(ThreadsManager::GROUP *group, int pos);

        std::atomic<bool> *get_stop_by_pos(ThreadsManager::GROUP *group, int pos);

        void remove_thread_by_pos(ThreadsManager::GROUP *group, int pos);
    }

}
