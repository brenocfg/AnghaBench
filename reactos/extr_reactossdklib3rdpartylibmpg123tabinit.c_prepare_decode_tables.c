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
typedef  int /*<<< orphan*/  real ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_TO_REAL (double) ; 
 double M_PI ; 
 double cos (double) ; 
 int /*<<< orphan*/ ** pnts ; 

void prepare_decode_tables()
{
#if !defined(REAL_IS_FIXED) || !defined(PRECALC_TABLES)
  int i,k,kr,divv;
  real *costab;

  for(i=0;i<5;i++)
  {
    kr=0x10>>i; divv=0x40>>i;
    costab = pnts[i];
    for(k=0;k<kr;k++)
      costab[k] = DOUBLE_TO_REAL(1.0 / (2.0 * cos(M_PI * ((double) k * 2.0 + 1.0) / (double) divv)));
  }
#endif
}