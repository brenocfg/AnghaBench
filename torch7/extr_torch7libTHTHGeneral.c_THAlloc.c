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
 void* THAllocInternal (int) ; 
 int /*<<< orphan*/  THError (char*,...) ; 
 int /*<<< orphan*/  torchGCData ; 
 int /*<<< orphan*/  torchGCFunction (int /*<<< orphan*/ ) ; 

void* THAlloc(ptrdiff_t size)
{
  void *ptr;

  if(size < 0)
    THError("$ Torch: invalid memory size -- maybe an overflow?");

  if(size == 0)
    return NULL;

  ptr = THAllocInternal(size);

  if(!ptr && torchGCFunction) {
    torchGCFunction(torchGCData);
    ptr = THAllocInternal(size);
  }

  if(!ptr)
    THError("$ Torch: not enough memory: you tried to allocate %dGB. Buy new RAM!", size/1073741824);

  return ptr;
}