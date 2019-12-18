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
typedef  int u_int64_t ;

/* Variables and functions */
 int INT64 (int) ; 
 int* T ; 
 int fls64 (int) ; 
 int polymmult (int,int,int) ; 
 int polymod (int /*<<< orphan*/ ,int,int) ; 
 int shift ; 

__attribute__((used)) static void calcT (u_int64_t poly)
{
    int j = 0;
    int xshift = fls64 (poly) - 1;
    shift = xshift - 8;
    u_int64_t T1 = polymod (0, INT64 (1) << xshift, poly);
    for (j = 0; j < 256; j++) {
        T[j] = polymmult (j, T1, poly) | ((u_int64_t) j << xshift);
    }
}