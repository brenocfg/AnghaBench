#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
struct mem {size_t next; size_t prev; int used; } ;

/* Variables and functions */
 scalar_t__ ERR_OK ; 
 int /*<<< orphan*/  LWIP_ASSERT (char*,int) ; 
 scalar_t__ LWIP_MEM_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWIP_RAM_HEAP_POINTER ; 
 int MEM_ALIGNMENT ; 
 size_t MEM_SIZE_ALIGNED ; 
 int /*<<< orphan*/  MEM_STATS_AVAIL (int /*<<< orphan*/ ,size_t) ; 
 int SIZEOF_STRUCT_MEM ; 
 int /*<<< orphan*/  avail ; 
 struct mem* lfree ; 
 int /*<<< orphan*/  mem_mutex ; 
 int /*<<< orphan*/ * ram ; 
 struct mem* ram_end ; 
 scalar_t__ sys_mutex_new (int /*<<< orphan*/ *) ; 

void
mem_init(void)
{
  struct mem *mem;

  LWIP_ASSERT("Sanity check alignment",
    (SIZEOF_STRUCT_MEM & (MEM_ALIGNMENT-1)) == 0);

  /* align the heap */
  ram = (u8_t *)LWIP_MEM_ALIGN(LWIP_RAM_HEAP_POINTER);
  /* initialize the start of the heap */
  mem = (struct mem *)(void *)ram;
  mem->next = MEM_SIZE_ALIGNED;
  mem->prev = 0;
  mem->used = 0;
  /* initialize the end of the heap */
  ram_end = (struct mem *)(void *)&ram[MEM_SIZE_ALIGNED];
  ram_end->used = 1;
  ram_end->next = MEM_SIZE_ALIGNED;
  ram_end->prev = MEM_SIZE_ALIGNED;

  /* initialize the lowest-free pointer to the start of the heap */
  lfree = (struct mem *)(void *)ram;

  MEM_STATS_AVAIL(avail, MEM_SIZE_ALIGNED);

  if(sys_mutex_new(&mem_mutex) != ERR_OK) {
    LWIP_ASSERT("failed to create mem_mutex", 0);
  }
}