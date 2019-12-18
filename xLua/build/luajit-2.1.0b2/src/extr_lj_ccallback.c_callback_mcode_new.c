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
struct TYPE_5__ {int /*<<< orphan*/  g; TYPE_1__ cb; int /*<<< orphan*/  L; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CTState ;

/* Variables and functions */
 scalar_t__ CALLBACK_MAX_SLOT ; 
 int /*<<< orphan*/  CALLBACK_MCODE_SIZE ; 
 int /*<<< orphan*/  LJ_ERR_FFI_CBACKOV ; 
 int MAP_ANONYMOUS ; 
 void* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 int /*<<< orphan*/  PAGE_EXECUTE_READ ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 void* VirtualAlloc (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualProtect (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callback_mcode_init (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lj_err_caller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lj_mcode_sync (void*,char*) ; 
 void* lj_mem_new (int /*<<< orphan*/ ,size_t) ; 
 void* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprotect (void*,size_t,int) ; 

__attribute__((used)) static void callback_mcode_new(CTState *cts)
{
  size_t sz = (size_t)CALLBACK_MCODE_SIZE;
  void *p;
  if (CALLBACK_MAX_SLOT == 0)
    lj_err_caller(cts->L, LJ_ERR_FFI_CBACKOV);
#if LJ_TARGET_WINDOWS
  p = VirtualAlloc(NULL, sz, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
  if (!p)
    lj_err_caller(cts->L, LJ_ERR_FFI_CBACKOV);
#elif LJ_TARGET_POSIX
  p = mmap(NULL, sz, (PROT_READ|PROT_WRITE), MAP_PRIVATE|MAP_ANONYMOUS,
	   -1, 0);
  if (p == MAP_FAILED)
    lj_err_caller(cts->L, LJ_ERR_FFI_CBACKOV);
#else
  /* Fallback allocator. Fails if memory is not executable by default. */
  p = lj_mem_new(cts->L, sz);
#endif
  cts->cb.mcode = p;
  callback_mcode_init(cts->g, p);
  lj_mcode_sync(p, (char *)p + sz);
#if LJ_TARGET_WINDOWS
  {
    DWORD oprot;
    VirtualProtect(p, sz, PAGE_EXECUTE_READ, &oprot);
  }
#elif LJ_TARGET_POSIX
  mprotect(p, sz, (PROT_READ|PROT_EXEC));
#endif
}