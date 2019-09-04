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

__attribute__((used)) static void test_VarR4ChangeTypeEx(void)
{
#ifdef HAS_UINT64_TO_FLOAT
  HRESULT hres;
  float in;
  VARIANTARG vSrc, vDst;

  in = 1.0f;

  INITIAL_TYPETEST(VT_R4, V_R4, "%f");
  COMMON_TYPETEST;
#endif
}