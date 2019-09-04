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
typedef  int /*<<< orphan*/  increment_t ;

/* Variables and functions */
 double INV_FP_ONE ; 
 double fp_fraction_part (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline double
fp_to_double (increment_t x)
{	return fp_fraction_part (x) * INV_FP_ONE ;
}