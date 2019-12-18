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
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  VALGRIND_DISCARD_TRANSLATIONS (void*,int) ; 
 int /*<<< orphan*/  __clear_cache (void*,void*) ; 
 int /*<<< orphan*/  lj_vm_cachesync (void*,void*) ; 
 int /*<<< orphan*/  sys_icache_invalidate (void*,int) ; 

void lj_mcode_sync(void *start, void *end)
{
#ifdef LUAJIT_USE_VALGRIND
  VALGRIND_DISCARD_TRANSLATIONS(start, (char *)end-(char *)start);
#endif
#if LJ_TARGET_X86ORX64
  UNUSED(start); UNUSED(end);
#elif LJ_TARGET_IOS
  sys_icache_invalidate(start, (char *)end-(char *)start);
#elif LJ_TARGET_PPC
  lj_vm_cachesync(start, end);
#elif defined(__GNUC__)
  __clear_cache(start, end);
#else
#error "Missing builtin to flush instruction cache"
#endif
}