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
 int /*<<< orphan*/  VT_BOOL ; 
 int /*<<< orphan*/  V_BOOL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_BOOLREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vDst ; 
 int /*<<< orphan*/  vSrc ; 

__attribute__((used)) static void test_VarBoolCopy(void)
{
  COPYTEST(1, VT_BOOL, V_BOOL(&vSrc), V_BOOL(&vDst), V_BOOLREF(&vSrc), V_BOOLREF(&vDst), "%d");
}