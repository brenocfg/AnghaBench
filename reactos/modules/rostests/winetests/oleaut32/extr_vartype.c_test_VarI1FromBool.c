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
 int /*<<< orphan*/  CONVERT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVERTRANGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (int) ; 
 int /*<<< orphan*/  VARIANT_BOOL ; 
 int /*<<< orphan*/  VarI1FromBool ; 

__attribute__((used)) static void test_VarI1FromBool(void)
{
  CONVVARS(VARIANT_BOOL);
  int i;

  /* Note that conversions from bool wrap around! */
  CONVERT(VarI1FromBool, -129);  EXPECT(127);
  CONVERTRANGE(VarI1FromBool, -128, 128);
  CONVERT(VarI1FromBool, 128); EXPECT(-128);
}