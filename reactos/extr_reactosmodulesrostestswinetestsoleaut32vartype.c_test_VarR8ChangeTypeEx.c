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

__attribute__((used)) static void test_VarR8ChangeTypeEx(void)
{
#ifdef HAS_UINT64_TO_FLOAT
  HRESULT hres;
  double in;
  VARIANTARG vSrc, vDst;

  in = 1.0;

  INITIAL_TYPETEST(VT_R8, V_R8, "%g");
  COMMON_TYPETEST;
#endif
}