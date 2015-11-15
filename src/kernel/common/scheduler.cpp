#include <scheduler.h>
#include <lf_os.h>
#include <string.h>

struct Scheduler::Task* Scheduler::_firstTask = 0;
struct Scheduler::Task* Scheduler::_lastTask = 0;
struct Scheduler::Task* Scheduler::_currentTask = 0;
pid_t Scheduler::_lastPid = 0;
bool Scheduler::_initialized = false;

void Scheduler::idleTask() {
    while(true) {
//        __asm__ __volatile__("hlt");
    }
}

void Scheduler::initialize() {
    _lastPid = 0;

    struct Task* idleTask = createNewTask(Scheduler::idleTask);

    _firstTask = idleTask;
    _lastTask = idleTask;
    _lastTask->next = _firstTask;
    _firstTask->prev = _lastTask;

    _initialized = true;
}

pid_t Scheduler::addTask(void(*task)()) {
    Task* newTask = createNewTask(task);
    insertTask(newTask);

    return newTask->pid;
}

struct cpu_state* Scheduler::nextTask(struct cpu_state* cpu) {
    if(!_initialized) {
        return cpu;
    }

    struct Task* current = _firstTask;
    while(current->next != _firstTask) {

        // schlafende Prozesse haben wieder einen Interrupt länger geschlafen
        if(current->sleeping_counter) {
            current->sleeping_counter--;
        }

        current = current->next;
    }

    if(_currentTask != 0) {
        // manche Tasks sind gleicher als andere
        _currentTask->priority_counter--;
        if(_currentTask->priority_counter) {
            return &_currentTask->cpu;
        }
  
        // wenn der aktuelle Task mal wieder dran kommt bleibt er so lange
        // aktiv wie seine Priorität sagt
        _currentTask->priority_counter = _currentTask->priority;

        memcpy((char*)&_currentTask->cpu, (char*)cpu, sizeof(struct cpu_state));
    }

    // neuen Task finden der aktiv ist und nicht schläft
    struct Task* newCurrent = _currentTask == 0 ? _firstTask : _currentTask->next;
    while(!newCurrent->active && !newCurrent->sleeping_counter) {
        newCurrent = newCurrent->next;
    }

    _currentTask = newCurrent;

    return &newCurrent->cpu;
}

struct Scheduler::Task* Scheduler::getTaskForPid(pid_t pid) {
    struct Task* current = _firstTask;
    while(current->pid != pid) {
        current = current->next;
    }

    if(current->pid == pid) {
        return current;
    }
    
    return 0;
}

struct Scheduler::Task* Scheduler::createNewTask(void(*task)()) {
    struct Task* newTask = (Task*)pmm_alloc();
    memset((char*)newTask, 0, PAGESIZE);

    newTask->priority = 1;
    newTask->priority_counter = 1;

    memcpy(newTask->name, "[no name]", 9);
    newTask->pid = _lastPid++;

    newTask->active = true;

    newTask->cpu.esp = (uint32_t)pmm_alloc() + 4096;
    newTask->cpu.eip = (uint32_t)task;
    newTask->cpu.cs  = 0x18 | 0x03;
    newTask->cpu.ss  = 0x20 | 0x03;
    newTask->cpu.eflags = 0x202;

    return newTask;
}

void Scheduler::insertTask(Task* newTask) {
    newTask->prev = _lastTask;
    newTask->next = _firstTask;

    _lastTask->next = newTask;
    _lastTask = newTask;
}
