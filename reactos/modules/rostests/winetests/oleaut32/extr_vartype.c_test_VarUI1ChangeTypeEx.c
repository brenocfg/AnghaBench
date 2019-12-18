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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_TYPETEST ; 
 int /*<<< orphan*/  INITIAL_TYPETEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NEGATIVE_TYPETEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_I1 ; 
 int /*<<< orphan*/  VT_UI1 ; 
 int /*<<< orphan*/  V_I1 ; 
 int /*<<< orphan*/  V_UI1 ; 

__attribute__((used)) static void test_VarUI1ChangeTypeEx(void)
{
  HRESULT hres;
  BYTE in;
  VARIANTARG vSrc, vDst;

  in = 1;

  INITIAL_TYPETEST(VT_UI1, V_UI1, "%d");
  COMMON_TYPETEST;
  NEGATIVE_TYPETEST(VT_UI1, V_UI1, "%d", VT_I1, V_I1);
}