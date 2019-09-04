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
 int /*<<< orphan*/  THArgCheck (int,int,char*) ; 
 double __uniform__ (int /*<<< orphan*/ *) ; 
 int log (double) ; 

int THRandom_geometric(THGenerator *_generator, double p)
{
  THArgCheck(p > 0 && p < 1, 1, "must be > 0 and < 1");
  return((int)(log(1-__uniform__(_generator)) / log(p)) + 1);
}