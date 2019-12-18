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
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsTransformFn ;
typedef  int /*<<< orphan*/  _cmsFreeUserDataFn ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TYPE_GRAY_8 ; 
 int /*<<< orphan*/  TrancendentalTransform ; 

cmsBool  TransformFactory(cmsContext ContextID, _cmsTransformFn* xformPtr,
                          void** UserData,
                           _cmsFreeUserDataFn* FreePrivateDataFn,
                           cmsPipeline** Lut,
                           cmsUInt32Number* InputFormat,
                           cmsUInt32Number* OutputFormat,
                           cmsUInt32Number* dwFlags)

{
    if (*OutputFormat == TYPE_GRAY_8)
    {
        // *Lut holds the pipeline to be applied
        *xformPtr = TrancendentalTransform;
        return TRUE;
    }

    return FALSE;
}