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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (float) ; 
 int /*<<< orphan*/  VARIANT_BOOL ; 
 float VARIANT_FALSE ; 
 float VARIANT_TRUE ; 
 int /*<<< orphan*/  VarR4FromBool ; 

__attribute__((used)) static void test_VarR4FromBool(void)
{
  CONVVARS(VARIANT_BOOL);

  CONVERT(VarR4FromBool, VARIANT_TRUE);  EXPECT(VARIANT_TRUE * 1.0f);
  CONVERT(VarR4FromBool, VARIANT_FALSE); EXPECT(VARIANT_FALSE * 1.0f);
}