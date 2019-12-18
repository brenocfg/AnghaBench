#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mcarea; } ;
typedef  TYPE_1__ jit_State ;

/* Variables and functions */
 int LJ_PRNG_BITS (TYPE_1__*,int) ; 
 int LJ_TARGET_JUMPRANGE ; 
 int /*<<< orphan*/  LJ_TRERR_MCODEAL ; 
 int /*<<< orphan*/  MCPROT_GEN ; 
 int /*<<< orphan*/  lj_trace_err (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lj_vm_exit_handler ; 
 void* mcode_alloc_at (TYPE_1__*,uintptr_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcode_free (TYPE_1__*,void*,size_t) ; 
 scalar_t__ mcode_validptr (void*) ; 

__attribute__((used)) static void *mcode_alloc(jit_State *J, size_t sz)
{
  /* Target an address in the static assembler code (64K aligned).
  ** Try addresses within a distance of target-range/2+1MB..target+range/2-1MB.
  ** Use half the jump range so every address in the range can reach any other.
  */
#if LJ_TARGET_MIPS
  /* Use the middle of the 256MB-aligned region. */
  uintptr_t target = ((uintptr_t)(void *)lj_vm_exit_handler & 0xf0000000u) +
		     0x08000000u;
#else
  uintptr_t target = (uintptr_t)(void *)lj_vm_exit_handler & ~(uintptr_t)0xffff;
#endif
  const uintptr_t range = (1u << (LJ_TARGET_JUMPRANGE-1)) - (1u << 21);
  /* First try a contiguous area below the last one. */
  uintptr_t hint = J->mcarea ? (uintptr_t)J->mcarea - sz : 0;
  int i;
  for (i = 0; i < 32; i++) {  /* 32 attempts ought to be enough ... */
    if (mcode_validptr(hint)) {
      void *p = mcode_alloc_at(J, hint, sz, MCPROT_GEN);

      if (mcode_validptr(p) &&
	  ((uintptr_t)p + sz - target < range || target - (uintptr_t)p < range))
	return p;
      if (p) mcode_free(J, p, sz);  /* Free badly placed area. */
    }
    /* Next try probing pseudo-random addresses. */
    do {
      hint = (0x78fb ^ LJ_PRNG_BITS(J, 15)) << 16;  /* 64K aligned. */
    } while (!(hint + sz < range));
    hint = target + hint - (range>>1);
  }
  lj_trace_err(J, LJ_TRERR_MCODEAL);  /* Give up. OS probably ignores hints? */
  return NULL;
}