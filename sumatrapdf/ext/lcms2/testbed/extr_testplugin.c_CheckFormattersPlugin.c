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
typedef  int cmsUInt16Number ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  DupContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FormattersPluginSample ; 
 int /*<<< orphan*/  FormattersPluginSample2 ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  TYPE_RGB_565 ; 
 int /*<<< orphan*/  WatchDogContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  cmsFLAGS_NULLTRANSFORM ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

cmsInt32Number CheckFormattersPlugin(void)
{
    cmsContext ctx = WatchDogContext(NULL);
    cmsContext cpy;
    cmsHTRANSFORM xform;
    cmsUInt16Number stream[]= { 0xffffU, 0x1234U, 0x0000U, 0x33ddU };
    cmsUInt16Number result[4];
    int i;

    cmsPlugin(ctx, &FormattersPluginSample);

    cpy = DupContext(ctx, NULL);

    cmsPlugin(cpy, &FormattersPluginSample2);

    xform = cmsCreateTransform(cpy, NULL, TYPE_RGB_565, NULL, TYPE_RGB_565, INTENT_PERCEPTUAL, cmsFLAGS_NULLTRANSFORM);

    cmsDoTransform(cpy, xform, stream, result, 4);

    cmsDeleteTransform(cpy, xform);
    cmsDeleteContext(ctx);
    cmsDeleteContext(cpy);

    for (i=0; i < 4; i++)
        if (stream[i] != result[i]) return 0;

    return 1;
}