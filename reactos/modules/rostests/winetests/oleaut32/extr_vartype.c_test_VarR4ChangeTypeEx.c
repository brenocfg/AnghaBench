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
typedef  int /*<<< orphan*/  VARIANTARG ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_TYPETEST ; 
 int /*<<< orphan*/  INITIAL_TYPETEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VT_R4 ; 
 int /*<<< orphan*/  V_R4 ; 

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