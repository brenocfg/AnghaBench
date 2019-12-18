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
typedef  int USHORT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_TYPETEST ; 
 int /*<<< orphan*/  INITIAL_TYPETEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NEGATIVE_TYPETEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_I2 ; 
 int /*<<< orphan*/  VT_UI2 ; 
 int /*<<< orphan*/  V_I2 ; 
 int /*<<< orphan*/  V_UI2 ; 

__attribute__((used)) static void test_VarUI2ChangeTypeEx(void)
{
  HRESULT hres;
  USHORT in;
  VARIANTARG vSrc, vDst;

  in = 1;

  INITIAL_TYPETEST(VT_UI2, V_UI2, "%d");
  COMMON_TYPETEST;
  NEGATIVE_TYPETEST(VT_UI2, V_UI2, "%d", VT_I2, V_I2);
}