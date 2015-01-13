#include <lf_os.h>

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
void *HardwareInterrupt(int number, void *cpu)
{
	// Todo: an Treiber weitergeben
	
	return cpu;
}

/** Bearbeitet einen Syscall
  * Wird vom architekturspezifischen Teil aufgerufen.
  * Die Parameter sind gleichzeitig auch Rückgabeparameter
  */
void Syscall(int number, unsigned int **params, int count)
{
	// Todo: mach etwas mit dem Syscall
}
