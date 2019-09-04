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
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BASE ; 
 int DAMP ; 
 int SKEW ; 
 int TMAX ; 
 int TMIN ; 

__attribute__((used)) static inline INT adapt(INT delta, INT numpoints, BOOL firsttime)
{
    INT k;

    delta /= (firsttime ? DAMP : 2);
    delta += delta/numpoints;

    for(k=0; delta>((BASE-TMIN)*TMAX)/2; k+=BASE)
        delta /= BASE-TMIN;
    return k+((BASE-TMIN+1)*delta)/(delta+SKEW);
}