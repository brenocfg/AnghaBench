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
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hColorTransform ; 
 int /*<<< orphan*/ * hInput ; 
 int /*<<< orphan*/ * hOutput ; 
 int /*<<< orphan*/ ** hProfiles ; 
 int /*<<< orphan*/ * hProof ; 
 int nProfiles ; 

__attribute__((used)) static
void CloseTransforms(void)
{
	int i;

	if (hColorTransform) cmsDeleteTransform(hColorTransform);
	if (hInput) cmsCloseProfile(hInput);
	if (hOutput) cmsCloseProfile(hOutput);             
	if (hProof) cmsCloseProfile(hProof);

	for (i=0; i < nProfiles; i++)
		cmsCloseProfile(hProfiles[i]);

	hColorTransform = NULL; hInput = NULL; hOutput = NULL; hProof = NULL;
}