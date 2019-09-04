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
 double RAND_MAX ; 
 double pow (double,double) ; 
 scalar_t__ rand () ; 

long long powerLawRand(long long min, long long max, double alpha) {
    double pl, r;

    max += 1;
    r = ((double)rand()) / RAND_MAX;
    pl = pow(
        ((pow(max,alpha+1) - pow(min,alpha+1))*r + pow(min,alpha+1)),
        (1.0/(alpha+1)));
    return (max-1-(long long)pl)+min;
}