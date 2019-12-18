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
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;

/* Variables and functions */
 int _cmsLCMScolorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int GetProfileColorSpace(cmsHPROFILE hProfile)
{
    cmsColorSpaceSignature ProfileSpace = cmsGetColorSpace(NULL, hProfile);

    return _cmsLCMScolorSpace(NULL, ProfileSpace);
}