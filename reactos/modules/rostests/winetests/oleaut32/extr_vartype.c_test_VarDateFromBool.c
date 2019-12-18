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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (double) ; 
 int /*<<< orphan*/  VARIANT_BOOL ; 
 double VARIANT_FALSE ; 
 double VARIANT_TRUE ; 
 int /*<<< orphan*/  VarDateFromBool ; 

__attribute__((used)) static void test_VarDateFromBool(void)
{
  CONVVARS(VARIANT_BOOL);

  CONVERT(VarDateFromBool, VARIANT_TRUE);  EXPECT(VARIANT_TRUE * 1.0);
  CONVERT(VarDateFromBool, VARIANT_FALSE); EXPECT(VARIANT_FALSE * 1.0);
}