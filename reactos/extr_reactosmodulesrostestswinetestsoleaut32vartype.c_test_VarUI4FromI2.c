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
 int /*<<< orphan*/  CONVERTRANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CONVVARS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVERFLOWRANGE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHORT ; 
 int /*<<< orphan*/  VarUI4FromI2 ; 

__attribute__((used)) static void test_VarUI4FromI2(void)
{
  CONVVARS(SHORT);
  int i;

  OVERFLOWRANGE(VarUI4FromI2, -32768, 0);
  CONVERTRANGE(VarUI4FromI2, 0, 32768);
}