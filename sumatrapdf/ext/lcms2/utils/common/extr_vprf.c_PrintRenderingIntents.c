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
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int SW ; 
 size_t cmsGetSupportedIntents (int /*<<< orphan*/ ,int,size_t*,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void PrintRenderingIntents(cmsContext ContextID)
{
    cmsUInt32Number Codes[200];
    char* Descriptions[200];
    cmsUInt32Number n, i;

    fprintf(stderr, "%ct<n> rendering intent:\n\n", SW);

    n = cmsGetSupportedIntents(ContextID, 200, Codes, Descriptions);

    for (i=0; i < n; i++) {
        fprintf(stderr, "\t%u - %s\n", Codes[i], Descriptions[i]);
    }
    fprintf(stderr, "\n");
}