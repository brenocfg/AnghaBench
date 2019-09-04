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
typedef  int /*<<< orphan*/  THGenerator ;

/* Variables and functions */
 double M_PI ; 
 double __uniform__ (int /*<<< orphan*/ *) ; 
 double tan (double) ; 

double THRandom_cauchy(THGenerator *_generator, double median, double sigma)
{
  return(median + sigma * tan(M_PI*(__uniform__(_generator)-0.5)));
}