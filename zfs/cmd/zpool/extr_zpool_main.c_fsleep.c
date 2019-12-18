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
struct timespec {float tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 float NANOSEC ; 
 scalar_t__ floor (float) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fsleep(float sec)
{
	struct timespec req;
	req.tv_sec = floor(sec);
	req.tv_nsec = (sec - (float)req.tv_sec) * NANOSEC;
	nanosleep(&req, NULL);
}