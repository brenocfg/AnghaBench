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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int drand (int /*<<< orphan*/ *) ; 
 int log (double) ; 
 double sqrt (int) ; 

__attribute__((used)) static void grand(double *r1, double *r2, uint32_t *seed)
{
    double s;
    double u1, u2;
    do {
        u1 = 2 * drand(seed) - 1;
        u2 = 2 * drand(seed) - 1;
        s = u1 * u1 + u2 * u2;
    } while (s >= 1.0);

    s = sqrt(-2 * log(s) / s);
    *r1 = u1 * s;
    *r2 = u2 * s;
}