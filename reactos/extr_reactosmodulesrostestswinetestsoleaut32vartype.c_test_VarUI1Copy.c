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
 int /*<<< orphan*/  COPYTEST (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VT_UI1 ; 
 int /*<<< orphan*/  V_UI1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI1REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vDst ; 
 int /*<<< orphan*/  vSrc ; 

__attribute__((used)) static void test_VarUI1Copy(void)
{
  COPYTEST(1, VT_UI1, V_UI1(&vSrc), V_UI1(&vDst), V_UI1REF(&vSrc), V_UI1REF(&vDst), "%d");
}