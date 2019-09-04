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
typedef  int ptrdiff_t ;

/* Variables and functions */
 void* THAlloc (int) ; 
 int /*<<< orphan*/  THError (char*,...) ; 
 int /*<<< orphan*/  THFree (void*) ; 
 int /*<<< orphan*/  THHeapUpdate (int) ; 
 int getAllocSize (void*) ; 
 void* realloc (void*,int) ; 
 int /*<<< orphan*/  torchGCData ; 
 int /*<<< orphan*/  torchGCFunction (int /*<<< orphan*/ ) ; 

void* THRealloc(void *ptr, ptrdiff_t size)
{
  if(!ptr)
    return(THAlloc(size));

  if(size == 0)
  {
    THFree(ptr);
    return NULL;
  }

  if(size < 0)
    THError("$ Torch: invalid memory size -- maybe an overflow?");

  ptrdiff_t oldSize = -getAllocSize(ptr);
  void *newptr = realloc(ptr, size);

  if(!newptr && torchGCFunction) {
    torchGCFunction(torchGCData);
    newptr = realloc(ptr, size);
  }

  if(!newptr)
    THError("$ Torch: not enough memory: you tried to reallocate %dGB. Buy new RAM!", size/1073741824);

  // update heapSize only after successfully reallocated
  THHeapUpdate(oldSize + getAllocSize(newptr));

  return newptr;
}