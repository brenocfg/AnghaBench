#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * Lerp16; } ;
struct TYPE_6__ {TYPE_3__ Interpolation; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  nOutputs; int /*<<< orphan*/  nInputs; } ;
typedef  TYPE_1__ cmsInterpParams ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_7__ {TYPE_3__ (* Interpolators ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ _cmsInterpPluginChunkType ;

/* Variables and functions */
 TYPE_3__ DefaultInterpolatorsFactory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InterpPlugin ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cmsBool _cmsSetInterpolationRoutine(cmsContext ContextID, cmsInterpParams* p)
{
    _cmsInterpPluginChunkType* ptr = (_cmsInterpPluginChunkType*) _cmsContextGetClientChunk(ContextID, InterpPlugin);

    p ->Interpolation.Lerp16 = NULL;

   // Invoke factory, possibly in the Plug-in
    if (ptr ->Interpolators != NULL)
        p ->Interpolation = ptr->Interpolators(ContextID, p -> nInputs, p ->nOutputs, p ->dwFlags);

    // If unsupported by the plug-in, go for the LittleCMS default.
    // If happens only if an extern plug-in is being used
    if (p ->Interpolation.Lerp16 == NULL)
        p ->Interpolation = DefaultInterpolatorsFactory(p ->nInputs, p ->nOutputs, p ->dwFlags);

    // Check for valid interpolator (we just check one member of the union)
    if (p ->Interpolation.Lerp16 == NULL) {
            return FALSE;
    }

    return TRUE;
}