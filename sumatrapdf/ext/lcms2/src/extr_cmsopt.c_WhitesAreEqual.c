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
typedef  size_t cmsUInt32Number ;
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int abs (scalar_t__) ; 

__attribute__((used)) static
cmsBool WhitesAreEqual(cmsUInt32Number n, cmsUInt16Number White1[], cmsUInt16Number White2[] )
{
    cmsUInt32Number i;

    for (i=0; i < n; i++) {

        if (abs(White1[i] - White2[i]) > 0xf000) return TRUE;  // Values are so extremely different that the fixup should be avoided
        if (White1[i] != White2[i]) return FALSE;
    }
    return TRUE;
}