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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pI10_OUTPUT ; 
 void* p__invalid_parameter ; 
 void* p_atan ; 
 void* p_exp ; 
 void* p_get_doserrno ; 
 void* p_get_errno ; 
 void* p_lfind_s ; 
 void* p_qsort_s ; 
 void* p_set_doserrno ; 
 void* p_set_errno ; 
 void* p_tanh ; 
 void* prand_s ; 
 void* pstrerror_s ; 

__attribute__((used)) static void init(void)
{
    HMODULE hmod = GetModuleHandleA("msvcrt.dll");

    prand_s = (void *)GetProcAddress(hmod, "rand_s");
    pI10_OUTPUT = (void*)GetProcAddress(hmod, "$I10_OUTPUT");
    pstrerror_s = (void *)GetProcAddress(hmod, "strerror_s");
    p_get_doserrno = (void *)GetProcAddress(hmod, "_get_doserrno");
    p_get_errno = (void *)GetProcAddress(hmod, "_get_errno");
    p_set_doserrno = (void *)GetProcAddress(hmod, "_set_doserrno");
    p_set_errno = (void *)GetProcAddress(hmod, "_set_errno");
    p__invalid_parameter = (void *)GetProcAddress(hmod, "_invalid_parameter");
    p_qsort_s = (void *)GetProcAddress(hmod, "qsort_s");
    p_atan = (void *)GetProcAddress(hmod, "atan");
    p_exp = (void *)GetProcAddress(hmod, "exp");
    p_tanh = (void *)GetProcAddress(hmod, "tanh");
    p_lfind_s = (void *)GetProcAddress(hmod, "_lfind_s");
}