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
 int /*<<< orphan*/  USHORT ; 
 int /*<<< orphan*/  VarR4FromUI2 ; 

__attribute__((used)) static void test_VarR4FromUI2(void)
{
  CONVVARS(USHORT);
  int i;

  CONVERTRANGE(VarR4FromUI2, 0, 65536);
}