#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * InterpolatorsFactory; } ;
typedef  TYPE_1__ cmsPluginInterpolation ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_4__ {int /*<<< orphan*/ * Interpolators; } ;
typedef  TYPE_2__ _cmsInterpPluginChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  InterpPlugin ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cmsBool  _cmsRegisterInterpPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    cmsPluginInterpolation* Plugin = (cmsPluginInterpolation*) Data;
    _cmsInterpPluginChunkType* ptr = (_cmsInterpPluginChunkType*) _cmsContextGetClientChunk(ContextID, InterpPlugin);

    if (Data == NULL) {

        ptr ->Interpolators = NULL;
        return TRUE;
    }

    // Set replacement functions
    ptr ->Interpolators = Plugin ->InterpolatorsFactory;
    return TRUE;
}