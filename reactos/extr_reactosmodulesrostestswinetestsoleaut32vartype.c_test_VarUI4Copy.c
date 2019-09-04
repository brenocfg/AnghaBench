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
 int /*<<< orphan*/  COPYTEST (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VT_UI4 ; 
 int /*<<< orphan*/  V_UI4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_UI4REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vDst ; 
 int /*<<< orphan*/  vSrc ; 

__attribute__((used)) static void test_VarUI4Copy(void)
{
  COPYTEST(1u, VT_UI4, V_UI4(&vSrc), V_UI4(&vDst), V_UI4REF(&vSrc), V_UI4REF(&vDst), "%u");
}