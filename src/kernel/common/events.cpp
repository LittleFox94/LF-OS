#include <lf_os.h>
#include <scheduler.h>
#include <syscalls.h>

/** Bearbeitet Exceptions die einen Absturz des Prozessors zufolge haben.
  * Diese Funktion darf nur aufgerufen werden wenn der Fehler nicht korrigiert
  * werden kann!
  */
void Exception(int number, char *errorMsg)
{
    crash(errorMsg);
}

/** Bearbeitet einen Hardwareinterrupt
  * Auf x86 wäre dies ein IRQ
  * Diese Funktion wird vom architekturspezifischen Teil aufgerufen.
  */
struct cpu_state* HardwareInterrupt(int number, struct cpu_state* cpu)
{
    // Todo: an Treiber weitergeben

    if(number == 0x20) {
        cpu = Scheduler::nextTask(cpu);
    }

    return cpu;
}

/** Bearbeitet einen Syscall
  * Wird vom architekturspezifischen Teil aufgerufen.
  * Die Parameter sind gleichzeitig auch Rückgabeparameter
  */
void Syscall(int number, unsigned int **params, int count, bool* change_task, struct cpu_state* cpu)
{
    SyscallGroup group = static_cast<SyscallGroup>(number >> 16);
    Syscalls syscall = static_cast<Syscalls>(number & 0xFFFF);

    switch(group) {
        case SyscallGroup::ProcessManagement:
            switch(syscall) {
                case Syscalls::Sleep:
                    Scheduler::sleep(*params[0]);
                    *change_task = true;
                    break;
                case Syscalls::Fork:
                    Scheduler::fork(cpu);
                    break;
                case Syscalls::GetProcessInfo:
                    *params[0] = Scheduler::getCurrentPid();
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
