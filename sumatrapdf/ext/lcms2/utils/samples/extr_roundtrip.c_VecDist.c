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
typedef  scalar_t__ cmsUInt8Number ;

/* Variables and functions */
 double fabs (scalar_t__) ; 
 double sqrt (double) ; 

__attribute__((used)) static
double VecDist(cmsUInt8Number bin[3], cmsUInt8Number bout[3])
{
       double rdist, gdist, bdist;

       rdist = fabs((double) bout[0] - bin[0]);
       gdist = fabs((double) bout[1] - bin[1]);
       bdist = fabs((double) bout[2] - bin[2]);

       return (sqrt((rdist*rdist + gdist*gdist + bdist*bdist)));
}