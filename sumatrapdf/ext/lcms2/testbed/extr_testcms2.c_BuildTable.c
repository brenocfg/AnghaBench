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
typedef  scalar_t__ cmsUInt16Number ;
typedef  int cmsInt32Number ;
typedef  int cmsFloat64Number ;
typedef  scalar_t__ cmsBool ;

/* Variables and functions */
 scalar_t__ floor (int) ; 

__attribute__((used)) static
void BuildTable(cmsInt32Number n, cmsUInt16Number Tab[], cmsBool  Descending)
{
    cmsInt32Number i;

    for (i=0; i < n; i++) {
        cmsFloat64Number v = (cmsFloat64Number) ((cmsFloat64Number) 65535.0 * i ) / (n-1);

        Tab[Descending ? (n - i - 1) : i ] = (cmsUInt16Number) floor(v + 0.5);
    }
}