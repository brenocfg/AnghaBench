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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/ * OpenStockProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutFile ; 
 int /*<<< orphan*/  cInProf ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t cmsGetPostScriptCSA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static
void GenerateCSA(cmsContext ContextID)
{
	cmsHPROFILE hProfile = OpenStockProfile(ContextID, cInProf);
	size_t n;
	char* Buffer;

	if (hProfile == NULL) return;

	n = cmsGetPostScriptCSA(ContextID, hProfile, Intent, 0, NULL, 0);
	if (n == 0) return;

    Buffer = (char*) malloc(n + 1);
    if (Buffer != NULL) {

        cmsGetPostScriptCSA(ContextID, hProfile, Intent, 0, Buffer, (cmsUInt32Number) n);
        Buffer[n] = 0;

        fprintf(OutFile, "%s", Buffer);

        free(Buffer);
    }

	cmsCloseProfile(ContextID, hProfile);
}