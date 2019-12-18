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
 int /*<<< orphan*/  DATE ; 
 int /*<<< orphan*/  EXPECTCY (double) ; 
 int /*<<< orphan*/  EXPECTCY64 (int,int) ; 
 int /*<<< orphan*/  EXPECT_OVERFLOW ; 
 int /*<<< orphan*/  VarCyFromDate ; 
 int /*<<< orphan*/  VarCyFromR8 ; 

__attribute__((used)) static void test_VarCyFromDate(void)
{
  CONVVARS(DATE);

#if defined(__i386__) && (defined(_MSC_VER) || defined(__GNUC__))
  CONVERT(VarCyFromR8, -461168601842738.7904); EXPECTCY64(0xbfffffff, 0xffffff23);
#endif

  CONVERT(VarCyFromDate, -1.0); EXPECTCY(-1);
  CONVERT(VarCyFromDate, -0.0); EXPECTCY(0);
  CONVERT(VarCyFromDate, 1.0);  EXPECTCY(1);
  CONVERT(VarCyFromDate, -4611686018427388416.1); EXPECT_OVERFLOW;
  CONVERT(VarCyFromDate, 4611686018427387648.0);  EXPECT_OVERFLOW;

  /* Rounding */
  CONVERT(VarCyFromDate, -1.5f);     EXPECTCY(-1.5);
  CONVERT(VarCyFromDate, -0.6f);     EXPECTCY(-0.6);
  CONVERT(VarCyFromDate, -0.5f);     EXPECTCY(-0.5);
  CONVERT(VarCyFromDate, -0.4f);     EXPECTCY(-0.4);
  CONVERT(VarCyFromDate, 0.4f);      EXPECTCY(0.4);
  CONVERT(VarCyFromDate, 0.5f);      EXPECTCY(0.5);
  CONVERT(VarCyFromDate, 0.6f);      EXPECTCY(0.6);
  CONVERT(VarCyFromDate, 1.5f);      EXPECTCY(1.5);
  CONVERT(VarCyFromDate, 1.00009f);  EXPECTCY(1.0001);
  CONVERT(VarCyFromDate, -1.00001f); EXPECTCY(-1);
  CONVERT(VarCyFromDate, -1.00005f); EXPECTCY(-1);
  CONVERT(VarCyFromDate, -0.00009f); EXPECTCY(-0.0001);
  CONVERT(VarCyFromDate, -0.00005f); EXPECTCY(0);
  CONVERT(VarCyFromDate, -0.00001f); EXPECTCY(0);
  CONVERT(VarCyFromDate, 0.00001f);  EXPECTCY(0);
  CONVERT(VarCyFromDate, 0.00005f);  EXPECTCY(0);
  CONVERT(VarCyFromDate, 0.00009f);  EXPECTCY(0.0001);
  CONVERT(VarCyFromDate, -1.00001f); EXPECTCY(-1);
  CONVERT(VarCyFromDate, -1.00005f); EXPECTCY(-1);
  CONVERT(VarCyFromDate, -1.00009f); EXPECTCY(-1.0001);
}