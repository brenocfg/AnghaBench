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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  float8 ;

/* Variables and functions */
 int /*<<< orphan*/  ldexp (double,int) ; 
 int pg_lrand48 () ; 

__attribute__((used)) static float8
calculate_jitter_percent()
{
	/* returns a number in the range [-0.125, 0.125] */
	/* right now we use the postgres user-space RNG. if we become worried about
	 * correlated schedulers we can switch to
	 *     pg_strong_random(&percent, sizeof(percent));
	 * though we would need to figure out a way to make our tests pass
	 */
	uint8 percent = pg_lrand48();
	return ldexp((double) (16 - (int) (percent % 32)), -7);
}