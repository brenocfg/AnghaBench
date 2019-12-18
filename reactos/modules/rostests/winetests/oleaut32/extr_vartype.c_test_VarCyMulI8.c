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
typedef  int /*<<< orphan*/  LONG64 ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECTCY (int) ; 
 int /*<<< orphan*/  EXPECTCY64 (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  MATHMULI8 (double,int) ; 
 int /*<<< orphan*/  MATHVARS1 ; 

__attribute__((used)) static void test_VarCyMulI8(void)
{
  MATHVARS1;
  LONG64 right;

  MATHMULI8(534443.0, 0); EXPECTCY(0);
  MATHMULI8(0.5, 1);      EXPECTCY(0.5);
  MATHMULI8(0.5, 2);      EXPECTCY(1);
  MATHMULI8(922337203685476.0, 1); EXPECTCY64(2147483647ul,4294951488ul);
  MATHMULI8(922337203685476.0, 2); EXPECT_OVERFLOW;
}