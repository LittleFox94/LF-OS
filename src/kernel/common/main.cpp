#include <lf_os.h>
#include <lf_ffs.h>

void kernelMain(char *ptrInitrd, int initrdLength)
{
	LF_FFS initrd(ptrInitrd);
}
