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

/* Variables and functions */
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

void *
_cdio_memdup (const void *mem, size_t count)
{
  void *new_mem = NULL;

  if (mem)
    {
      new_mem = calloc (1, count);
      cdio_assert (new_mem != NULL);
      memcpy (new_mem, mem, count);
    }

  return new_mem;
}