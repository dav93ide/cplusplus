/*
    Compilation:
        g++ test_threads_manager.cpp ThreadsManager/ThreadsManager.cpp -pthread
*/

#include "../ThreadsManager/ThreadsManager.h"
#include <iostream>
#include <unistd.h>
#include <atomic>

void test(const char *blabla, int s, std::atomic<bool> *stop){
    while(!*stop){
        std::cout << blabla << " -> " << "Doing Work lolol\n";
        std::this_thread::sleep_for(std::chrono::seconds(s));

    }
}

ThreadsManager::GROUP group;

void print_group(){
    if(group.count > 0x0){
        std::cout << "\n\n\t\tMAIN -> Group.count = " << group.count << std::endl;
        int cnt = group.count;
        for(int i = 0x0; cnt > 0x0; i++){
            if(group.handles[i] != nullptr){
                cnt--;
                std::cout << "\n\n\t\tMAIN -> i = " << i << " IS NOT NULL! " << std::endl;
            }
        }
    }
}

int main(){
    group = {0x0, {}, {}, {}};

    std::thread one(test, "One", 2, ThreadsManager::add_thread(&group, &one, 0x1));
    std::thread two(test, "Two", 5, ThreadsManager::add_thread(&group, &two, 0x2));
    std::thread three(test, "Three", 7, ThreadsManager::add_thread(&group, &three, 0x3));

    std::cout << "\t\tMAIN -> detaching..." << std::endl;
    one.detach();
    two.detach();
    three.detach();

    std::cout << "\t\tMAIN -> SLEEP 10... ZzZZZZzzzZZzzz" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "\t\tMAIN -> WAKE UP!" << std::endl;
    
    std::cout << "\n\t\tMAIN ->Stop Thread ONE..." << std::endl;
    if(ThreadsManager::stop_and_remove_thread(&group, 0x1)){
        std::cout << "\n\t\tMAIN -> Thread ONE Stopped..." << std::endl;
    }
    std::cout << "\t\tMAIN -> SLEEP 10... ZzZZZZzzzZZzzz" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    print_group();

    std::cout << "\n\t\tMAIN ->Stop Thread TWO..." << std::endl;
    if(ThreadsManager::stop_and_remove_thread(&group, 0x2)){
        std::cout << "\n\t\tMAIN -> Thread TWO Stopped..." << std::endl;
    }
    std::cout << "\t\tMAIN -> SLEEP 10... ZzZZZZzzzZZzzz" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    print_group();

    std::cout << "\n\t\tMAIN ->Stop Thread THREE..." << std::endl;
    if(ThreadsManager::stop_and_remove_thread(&group, 0x3)){
        std::cout << "\n\t\tMAIN -> Thread THREE Stopped..." << std::endl;
    }
    std::cout << "\t\tMAIN -> SLEEP 10... ZzZZZZzzzZZzzz" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    print_group();

    return 0x0;
}