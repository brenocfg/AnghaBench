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
 int /*<<< orphan*/  DATE ; 
 int /*<<< orphan*/  EXPECTDEC (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VarDecFromDate ; 

__attribute__((used)) static void test_VarDecFromDate(void)
{
  CONVVARS(DATE);

  CONVERT(VarDecFromDate,-0.6); EXPECTDEC(1,0x80,0,6);
  CONVERT(VarDecFromDate,-0.5); EXPECTDEC(1,0x80,0,5);
  CONVERT(VarDecFromDate,-0.4); EXPECTDEC(1,0x80,0,4);
  CONVERT(VarDecFromDate,0.0);  EXPECTDEC(0,0,0,0);
  CONVERT(VarDecFromDate,0.4);  EXPECTDEC(1,0,0,4);
  CONVERT(VarDecFromDate,0.5);  EXPECTDEC(1,0,0,5);
  CONVERT(VarDecFromDate,0.6);  EXPECTDEC(1,0,0,6);
}