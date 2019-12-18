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
typedef  int cmsUInt32Number ;
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 scalar_t__ InHexa ; 
 int /*<<< orphan*/  OutputColorSpace ; 
 int /*<<< orphan*/ * OutputColorant ; 
 scalar_t__ Verbose ; 
 scalar_t__ Width16 ; 
 int cmsChannelsOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsMAX_PATH ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ floor (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static
void PrintEncodedResults(cmsContext ContextID, cmsUInt16Number Encoded[])
{
    cmsUInt32Number i, n;
    char ChannelName[cmsMAX_PATH];
    cmsUInt32Number v;

    n = cmsChannelsOf(ContextID, OutputColorSpace);
    for (i=0; i < n; i++) {

        if (OutputColorant != NULL) {

            cmsNamedColorInfo(ContextID, OutputColorant, i, ChannelName, NULL, NULL, NULL, NULL);
        }
        else {
            sprintf(ChannelName, "Channel #%u", i + 1);
        }

        if (Verbose > 0)
            printf("%s=", ChannelName);

        v = Encoded[i];

        if (InHexa) {

            if (Width16)
                printf("0x%04X ", (int) floor(v + .5));
            else
                printf("0x%02X ", (int) floor(v / 257. + .5));

        } else {

            if (Width16)
                printf("%d ", (int) floor(v + .5));
            else
                printf("%d ", (int) floor(v / 257. + .5));
        }

    }

    printf("\n");
}