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
typedef  int time_t ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime (int*) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 int mktime (int /*<<< orphan*/ ) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double LocalTZA(void)
{
	static int once = 1;
	static double tza = 0;
	if (once) {
		time_t now = time(NULL);
		time_t utc = mktime(gmtime(&now));
		time_t loc = mktime(localtime(&now));
		tza = (loc - utc) * 1000;
		once = 0;
	}
	return tza;
}