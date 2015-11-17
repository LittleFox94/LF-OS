#ifndef _SCHEDULER_H_INCLUDED
#define _SCHEDULER_H_INCLUDED

#include <lf_os.h>

typedef int16_t pid_t;

class Scheduler {
    public:
        static void initialize();

        static pid_t addTask(void(*task)(), bool kernel=false);
        static struct cpu_state* nextTask(struct cpu_state* current);

        static void idleTask();
       
        static void sleep(uint32_t numInterrupts);
        static void fork();

        struct Task {
            uint8_t priority;
            uint8_t priority_counter;

            uint64_t sleeping_counter;

            char name[256];
            pid_t pid;

            bool active;

            bool there_was_a_fork;
            bool i_am_the_new_fork;

            struct Task* next;
            struct Task* prev;
            
            struct cpu_state cpu;
        }__attribute__((packed));

    private:
        static struct Task* getTaskForPid(pid_t pid);
        static struct Task* createNewTask(void(*task)(), bool kernel=false);
        static void insertTask(Task* task);

        static struct Task* _firstTask;
        static struct Task* _lastTask;
        static struct Task* _currentTask;
        static pid_t _lastPid;
        static bool _initialized;
};

#endif
