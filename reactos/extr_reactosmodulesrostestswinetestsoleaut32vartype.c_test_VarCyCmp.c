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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CY ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_EQ ; 
 int /*<<< orphan*/  EXPECT_GT ; 
 int /*<<< orphan*/  EXPECT_LT ; 
 int /*<<< orphan*/  MATHCMP (double,double) ; 

__attribute__((used)) static void test_VarCyCmp(void)
{
  HRESULT hres;
  double left = 0.0, right = 0.0;
  CY cyLeft, cyRight;

  MATHCMP(-1.0, -1.0); EXPECT_EQ;
  MATHCMP(-1.0, 0.0);  EXPECT_LT;
  MATHCMP(-1.0, 1.0);  EXPECT_LT;
  MATHCMP(-1.0, 2.0);  EXPECT_LT;
  MATHCMP(0.0, 1.0);   EXPECT_LT;
  MATHCMP(0.0, 0.0);   EXPECT_EQ;
  MATHCMP(0.0, -1.0);  EXPECT_GT;
  MATHCMP(1.0, -1.0);  EXPECT_GT;
  MATHCMP(1.0, 0.0);   EXPECT_GT;
  MATHCMP(1.0, 1.0);   EXPECT_EQ;
  MATHCMP(1.0, 2.0);   EXPECT_LT;
}