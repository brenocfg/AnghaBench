#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* mcode; } ;
struct TYPE_5__ {int /*<<< orphan*/  g; TYPE_1__ cb; } ;
typedef  TYPE_2__ CTState ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK_MCODE_SIZE ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  UNUSED (size_t) ; 
 int /*<<< orphan*/  VirtualFree (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_mem_free (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 

void lj_ccallback_mcode_free(CTState *cts)
{
  size_t sz = (size_t)CALLBACK_MCODE_SIZE;
  void *p = cts->cb.mcode;
  if (p == NULL) return;
#if LJ_TARGET_WINDOWS
  VirtualFree(p, 0, MEM_RELEASE);
  UNUSED(sz);
#elif LJ_TARGET_POSIX
  munmap(p, sz);
#else
  lj_mem_free(cts->g, p, sz);
#endif
}