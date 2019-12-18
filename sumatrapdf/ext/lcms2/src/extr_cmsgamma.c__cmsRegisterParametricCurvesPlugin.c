#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt32Number ;
struct TYPE_4__ {int nFunctions; int /*<<< orphan*/  ParameterCount; int /*<<< orphan*/  FunctionTypes; int /*<<< orphan*/  Evaluator; } ;
typedef  TYPE_1__ cmsPluginParametricCurves ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {int nFunctions; struct TYPE_5__* Next; int /*<<< orphan*/  ParameterCount; int /*<<< orphan*/  FunctionTypes; int /*<<< orphan*/  Evaluator; } ;
typedef  TYPE_2__ _cmsParametricCurvesCollection ;
struct TYPE_6__ {TYPE_2__* ParametricCurves; } ;
typedef  TYPE_3__ _cmsCurvesPluginChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  CurvesPlugin ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_TYPES_IN_LCMS_PLUGIN ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsPluginMalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

cmsBool _cmsRegisterParametricCurvesPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    _cmsCurvesPluginChunkType* ctx = ( _cmsCurvesPluginChunkType*) _cmsContextGetClientChunk(ContextID, CurvesPlugin);
    cmsPluginParametricCurves* Plugin = (cmsPluginParametricCurves*) Data;
    _cmsParametricCurvesCollection* fl;

    if (Data == NULL) {

          ctx -> ParametricCurves =  NULL;
          return TRUE;
    }

    fl = (_cmsParametricCurvesCollection*) _cmsPluginMalloc(ContextID, sizeof(_cmsParametricCurvesCollection));
    if (fl == NULL) return FALSE;

    // Copy the parameters
    fl ->Evaluator  = Plugin ->Evaluator;
    fl ->nFunctions = Plugin ->nFunctions;

    // Make sure no mem overwrites
    if (fl ->nFunctions > MAX_TYPES_IN_LCMS_PLUGIN)
        fl ->nFunctions = MAX_TYPES_IN_LCMS_PLUGIN;

    // Copy the data
    memmove(fl->FunctionTypes,  Plugin ->FunctionTypes,   fl->nFunctions * sizeof(cmsUInt32Number));
    memmove(fl->ParameterCount, Plugin ->ParameterCount,  fl->nFunctions * sizeof(cmsUInt32Number));

    // Keep linked list
    fl ->Next = ctx->ParametricCurves;
    ctx->ParametricCurves = fl;

    // All is ok
    return TRUE;
}