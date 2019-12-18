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
typedef  double cmsUInt32Number ;
typedef  double cmsFloat64Number ;

/* Variables and functions */
 double CLOCKS_PER_SEC ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
void PrintPerformance(cmsUInt32Number Bytes, cmsUInt32Number SizeOfPixel, cmsFloat64Number diff)
{
    cmsFloat64Number seconds  = (cmsFloat64Number) diff / CLOCKS_PER_SEC;
    cmsFloat64Number mpix_sec = Bytes / (1024.0*1024.0*seconds*SizeOfPixel);

    printf("%#4.3g MPixel/sec.\n", mpix_sec);
    fflush(stdout);
}