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
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  GetIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLine (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  InputColorSpace ; 
 scalar_t__ InputColorant ; 
 scalar_t__ InputNamedColor ; 
 int InputRange ; 
 scalar_t__ atof (char*) ; 
 int cmsChannelsOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsMAX_PATH ; 
 int /*<<< orphan*/  cmsNamedColorInfo (int /*<<< orphan*/ ,scalar_t__,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ xisatty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void TakeFloatValues(cmsContext ContextID, cmsFloat64Number Float[])
{
    cmsUInt32Number i, n;
    char ChannelName[cmsMAX_PATH];
    char Buffer[4096];

    if (xisatty(stdin))
        fprintf(stderr, "\nEnter values, 'q' to quit\n");

    if (InputNamedColor) {

        // This is named color index, which is always cmsUInt16Number
        cmsUInt16Number index = GetIndex(ContextID);
        memcpy(Float, &index, sizeof(cmsUInt16Number));
        return;
    }

    n = cmsChannelsOf(ContextID, InputColorSpace);
    for (i=0; i < n; i++) {

        if (InputColorant) {
            cmsNamedColorInfo(ContextID, InputColorant, i, ChannelName, NULL, NULL, NULL, NULL);
        }
        else {
            InputRange = 1;
            sprintf(ChannelName, "Channel #%u", i+1);
        }

        GetLine(ContextID, Buffer, "%s? ", ChannelName);

        Float[i] = (cmsFloat64Number) atof(Buffer) / InputRange;
    }

    if (xisatty(stdin))
        fprintf(stderr, "\n");
}