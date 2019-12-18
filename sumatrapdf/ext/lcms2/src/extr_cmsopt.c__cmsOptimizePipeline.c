#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
struct TYPE_11__ {int /*<<< orphan*/ * Elements; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_12__ {TYPE_3__* OptimizationCollection; } ;
typedef  TYPE_2__ _cmsOptimizationPluginChunkType ;
struct TYPE_13__ {scalar_t__ (* OptimizePtr ) (int /*<<< orphan*/ ,TYPE_1__**,int,int*,int*,int*) ;struct TYPE_13__* Next; } ;
typedef  TYPE_3__ _cmsOptimizationCollection ;

/* Variables and functions */
 TYPE_3__* DefaultOptimization ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FastIdentity16 ; 
 int /*<<< orphan*/  OptimizationPlugin ; 
 int /*<<< orphan*/  OptimizeByResampling (int /*<<< orphan*/ ,TYPE_1__**,int,int*,int*,int*) ; 
 int /*<<< orphan*/  PreOptimize (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsPipelineSetOptimizationParameters (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cmsFLAGS_FORCE_CLUT ; 
 int cmsFLAGS_NOOPTIMIZE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__**,int,int*,int*,int*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_1__**,int,int*,int*,int*) ; 

cmsBool _cmsOptimizePipeline(cmsContext ContextID,
                             cmsPipeline**    PtrLut,
                             cmsUInt32Number  Intent,
                             cmsUInt32Number* InputFormat,
                             cmsUInt32Number* OutputFormat,
                             cmsUInt32Number* dwFlags)
{
    _cmsOptimizationPluginChunkType* ctx = ( _cmsOptimizationPluginChunkType*) _cmsContextGetClientChunk(ContextID, OptimizationPlugin);
    _cmsOptimizationCollection* Opts;
    cmsBool AnySuccess = FALSE;

    // A CLUT is being asked, so force this specific optimization
    if (*dwFlags & cmsFLAGS_FORCE_CLUT) {

        PreOptimize(ContextID, *PtrLut);
        return OptimizeByResampling(ContextID, PtrLut, Intent, InputFormat, OutputFormat, dwFlags);
    }

    // Anything to optimize?
    if ((*PtrLut) ->Elements == NULL) {
        _cmsPipelineSetOptimizationParameters(ContextID, *PtrLut, FastIdentity16, (void*) *PtrLut, NULL, NULL);
        return TRUE;
    }

    // Try to get rid of identities and trivial conversions.
    AnySuccess = PreOptimize(ContextID, *PtrLut);

    // After removal do we end with an identity?
    if ((*PtrLut) ->Elements == NULL) {
        _cmsPipelineSetOptimizationParameters(ContextID, *PtrLut, FastIdentity16, (void*) *PtrLut, NULL, NULL);
        return TRUE;
    }

    // Do not optimize, keep all precision
    if (*dwFlags & cmsFLAGS_NOOPTIMIZE)
        return FALSE;

    // Try plug-in optimizations
    for (Opts = ctx->OptimizationCollection;
         Opts != NULL;
         Opts = Opts ->Next) {

            // If one schema succeeded, we are done
            if (Opts ->OptimizePtr(ContextID, PtrLut, Intent, InputFormat, OutputFormat, dwFlags)) {

                return TRUE;    // Optimized!
            }
    }

   // Try built-in optimizations
    for (Opts = DefaultOptimization;
         Opts != NULL;
         Opts = Opts ->Next) {

            if (Opts ->OptimizePtr(ContextID, PtrLut, Intent, InputFormat, OutputFormat, dwFlags)) {

                return TRUE;
            }
    }

    // Only simple optimizations succeeded
    return AnySuccess;
}