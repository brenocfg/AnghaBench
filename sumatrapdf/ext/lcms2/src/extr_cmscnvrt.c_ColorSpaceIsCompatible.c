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
typedef  scalar_t__ cmsColorSpaceSignature ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ cmsSig4colorData ; 
 scalar_t__ cmsSigCmykData ; 
 scalar_t__ cmsSigLabData ; 
 scalar_t__ cmsSigXYZData ; 

__attribute__((used)) static
cmsBool ColorSpaceIsCompatible(cmsColorSpaceSignature a, cmsColorSpaceSignature b)
{
    // If they are same, they are compatible.
    if (a == b) return TRUE;

    // Check for MCH4 substitution of CMYK
    if ((a == cmsSig4colorData) && (b == cmsSigCmykData)) return TRUE;
    if ((a == cmsSigCmykData) && (b == cmsSig4colorData)) return TRUE;

    // Check for XYZ/Lab. Those spaces are interchangeable as they can be computed one from other.
    if ((a == cmsSigXYZData) && (b == cmsSigLabData)) return TRUE;
    if ((a == cmsSigLabData) && (b == cmsSigXYZData)) return TRUE;

    return FALSE;
}