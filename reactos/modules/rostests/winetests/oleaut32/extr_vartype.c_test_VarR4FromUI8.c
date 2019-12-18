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
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT (float) ; 
 int /*<<< orphan*/  ULONG64 ; 
 int /*<<< orphan*/  VarR4FromUI8 ; 

__attribute__((used)) static void test_VarR4FromUI8(void)
{
  CONVVARS(ULONG64);

  CONVERT(VarR4FromUI8, 0); EXPECT(0.0f);
  CONVERT(VarR4FromUI8, 1); EXPECT(1.0f);
}