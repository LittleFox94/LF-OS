#include <lf_os.h>

/** This is the bitmap of the physical memory management
  */
uint64_t PmmBitmap[PMMBITMAPSIZE];

/** This variable stores the first memory address known to be free
  */
void *firstKnownFreeAddress = null;

// statt uint8_t wäre void eigentlich die bessere Wahl
// gibt allerdings einen Compilerfehler
extern const uint8_t kernel_start;
extern const uint8_t kernel_end;

/** To be called from architecture specific starter.
  * After initializing the physical memory manager the architecture specific
  * starter has to mark already used memorylocations, such as the initrd and
  * other stuff loaded by bootloader
  */
void init_pmm()
{
	for(uint64_t i = 0; i < PMMBITMAPSIZE; i++)
	{
		PmmBitmap[i] = 0;
	}
	
	for(uint64_t i = (uint32_t)&kernel_start; i < (uint32_t)&kernel_end; i += PAGESIZE)
	{
		pmm_mark_used((void*)i);
	}
	
	pmm_mark_used(null);
}

/** Mark one page as used
  * <param=mem>memory address of the block</param>
  */
void pmm_mark_used(void *mem)
{
	uint64_t page = (uint32_t)mem / PAGESIZE;
	
	uint64_t index = page / 64;
	uint32_t bit = page % 64;
	
	PmmBitmap[index] |= (1 << bit);
	
	while(!pmm_check_free(firstKnownFreeAddress))
	{
		firstKnownFreeAddress = (void*)((uint64_t)firstKnownFreeAddress + PAGESIZE);
	}
}

/** Mark one page as free
  * <param=mem>memory address of the block</param>
  */
void pmm_mark_free(void *mem)
{
	uint64_t page = (uint32_t)mem / PAGESIZE;
	
	uint64_t index = page / 64;
	uint32_t bit = page % 64;
	
	PmmBitmap[index] &= ~(1 << bit);
	
	if(mem < firstKnownFreeAddress)
		firstKnownFreeAddress = mem;
}

/** Check if a page is marked as free
  * <param=mem>memory address of the block</param>
  * <return>true if the page is free; false if isn't</return>
  */
bool pmm_check_free(void *mem)
{
	uint64_t page = (uint32_t)mem / PAGESIZE;
	
	uint64_t index = page / 64;
	uint32_t bit = page % 64;
	
	return (PmmBitmap[index] & (1 << bit)) == 0;
}

/** Seeks an unused page, mark it as used and returns it's address
  * <return>address of the allocated page; null if nothing found</return>
  * <remarks>you should free unused pages with pmm_mark_free()</remarks>
  */
void *pmm_alloc()
{
	for(uint64_t addr = (uint64_t)firstKnownFreeAddress; addr < MAXMEM; addr += PAGESIZE)
	{
		if(pmm_check_free((void*)addr))
		{
			pmm_mark_used((void*)addr);
			
			return (void*)addr;
		}
	}
	
	return null;
}

/** Allocates a block of memory with 'size' bytes.
  * <param=size>size of the block</param>
  * <return>pointer to block; null if nothing found</return>
  * <remarks>the size of the allocated block is rounded up to powers of 'PAGESIZE'</remarks>
  */
void *pmm_multi_alloc(size_t size)
{
	uint32_t num_pages = size / PAGESIZE + (size % PAGESIZE >= 1 ? PAGESIZE : 0);
	
	for(uint64_t addr = (uint64_t)firstKnownFreeAddress; addr < MAXMEM; addr += PAGESIZE)
	{
		bool is_free = true;
		
		uint64_t tempAddr = addr;
		uint32_t pages = 0;
		
		while(pages < num_pages && is_free)
		{
			is_free = pmm_check_free((void*)tempAddr);
			
			tempAddr += PAGESIZE;
			pages++;
		}
		
		if(is_free)
		{
			pages = 0;
			
			for(; pages < num_pages; pages++)
			{
				pmm_mark_used((void*)(addr + (pages * PAGESIZE))); // mark memory as used
			}
			
			return (void*)addr;
		}
		else
			addr = tempAddr; // don't check some addresses twice
	}
	
	return null;
}
