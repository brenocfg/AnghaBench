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
typedef  int /*<<< orphan*/  jit_State ;

/* Variables and functions */
 int /*<<< orphan*/  LJ_TRERR_MCODEAL ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  lj_trace_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *mcode_alloc_at(jit_State *J, uintptr_t hint, size_t sz, int prot)
{
  void *p = mmap((void *)hint, sz, prot, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED) {
    if (!hint) lj_trace_err(J, LJ_TRERR_MCODEAL);
    p = NULL;
  }
  return p;
}