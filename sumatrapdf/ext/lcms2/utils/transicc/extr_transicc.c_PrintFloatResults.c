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
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  OutputColorSpace ; 
 int /*<<< orphan*/ * OutputColorant ; 
 double OutputRange ; 
 scalar_t__ Verbose ; 
 int cmsChannelsOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsMAX_PATH ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double floor (double) ; 
 scalar_t__ lQuantize ; 
 int /*<<< orphan*/  lUnbounded ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static
void PrintFloatResults(cmsContext ContextID, cmsFloat64Number Value[])
{
    cmsUInt32Number i, n;
    char ChannelName[cmsMAX_PATH];
    cmsFloat64Number v;

    n = cmsChannelsOf(ContextID, OutputColorSpace);
    for (i=0; i < n; i++) {

        if (OutputColorant != NULL) {

            cmsNamedColorInfo(ContextID, OutputColorant, i, ChannelName, NULL, NULL, NULL, NULL);
        }
        else {
            OutputRange = 1;
            sprintf(ChannelName, "Channel #%u", i + 1);
        }

        v = (cmsFloat64Number) Value[i]* OutputRange;

        if (lQuantize)
            v = floor(v + 0.5);

        if (!lUnbounded) {

               if (v < 0)
                      v = 0;
               if (v > OutputRange)
                      v = OutputRange;
        }

        if (Verbose <= 0)
            printf("%.4f ", v);
        else
            printf("%s=%.4f ", ChannelName, v);
    }

    printf("\n");
}