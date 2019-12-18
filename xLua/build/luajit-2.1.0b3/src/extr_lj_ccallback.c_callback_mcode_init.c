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
typedef  void* uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  global_State ;
typedef  int MSize ;

/* Variables and functions */
 int CALLBACK_MAX_SLOT ; 
 int CALLBACK_MCODE_SIZE ; 
 int RID_EAX ; 
 int RID_EBP ; 
 int /*<<< orphan*/  XI_GROUP5 ; 
 int /*<<< orphan*/  XI_JMP ; 
 int /*<<< orphan*/  XI_JMPs ; 
 int XI_MOVri ; 
 int XI_MOVrib ; 
 int XI_PUSH ; 
 int XM_OFS0 ; 
 int XOg_JMP ; 
 int i32ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ lj_vm_ffi_callback ; 
 int /*<<< orphan*/  lua_assert (int) ; 

__attribute__((used)) static void callback_mcode_init(global_State *g, uint8_t *page)
{
  uint8_t *p = page;
  uint8_t *target = (uint8_t *)(void *)lj_vm_ffi_callback;
  MSize slot;
#if LJ_64
  *(void **)p = target; p += 8;
#endif
  for (slot = 0; slot < CALLBACK_MAX_SLOT; slot++) {
    /* mov al, slot; jmp group */
    *p++ = XI_MOVrib | RID_EAX; *p++ = (uint8_t)slot;
    if ((slot & 31) == 31 || slot == CALLBACK_MAX_SLOT-1) {
      /* push ebp/rbp; mov ah, slot>>8; mov ebp, &g. */
      *p++ = XI_PUSH + RID_EBP;
      *p++ = XI_MOVrib | (RID_EAX+4); *p++ = (uint8_t)(slot >> 8);
#if LJ_GC64
      *p++ = 0x48; *p++ = XI_MOVri | RID_EBP;
      *(uint64_t *)p = (uint64_t)(g); p += 8;
#else
      *p++ = XI_MOVri | RID_EBP;
      *(int32_t *)p = i32ptr(g); p += 4;
#endif
#if LJ_64
      /* jmp [rip-pageofs] where lj_vm_ffi_callback is stored. */
      *p++ = XI_GROUP5; *p++ = XM_OFS0 + (XOg_JMP<<3) + RID_EBP;
      *(int32_t *)p = (int32_t)(page-(p+4)); p += 4;
#else
      /* jmp lj_vm_ffi_callback. */
      *p++ = XI_JMP; *(int32_t *)p = target-(p+4); p += 4;
#endif
    } else {
      *p++ = XI_JMPs; *p++ = (uint8_t)((2+2)*(31-(slot&31)) - 2);
    }
  }
  lua_assert(p - page <= CALLBACK_MCODE_SIZE);
}