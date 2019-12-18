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
 int /*<<< orphan*/  CONVERTRANGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVERFLOWRANGE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SHORT ; 
 int /*<<< orphan*/  VarI1FromI2 ; 

__attribute__((used)) static void test_VarI1FromI2(void)
{
  CONVVARS(SHORT);
  int i;

  OVERFLOWRANGE(VarI1FromI2, -32768, -128);
  CONVERTRANGE(VarI1FromI2, -128, 128);
  OVERFLOWRANGE(VarI1FromI2, 129, 32768);
}