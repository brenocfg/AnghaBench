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
struct TYPE_4__ {int /*<<< orphan*/ * OptimizePtr; } ;
typedef  TYPE_1__ cmsPluginOptimization ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {TYPE_3__* OptimizationCollection; } ;
typedef  TYPE_2__ _cmsOptimizationPluginChunkType ;
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/ * OptimizePtr; } ;
typedef  TYPE_3__ _cmsOptimizationCollection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OptimizationPlugin ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsPluginMalloc (int /*<<< orphan*/ ,int) ; 

cmsBool  _cmsRegisterOptimizationPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    cmsPluginOptimization* Plugin = (cmsPluginOptimization*) Data;
    _cmsOptimizationPluginChunkType* ctx = ( _cmsOptimizationPluginChunkType*) _cmsContextGetClientChunk(ContextID, OptimizationPlugin);
    _cmsOptimizationCollection* fl;

    if (Data == NULL) {

        ctx->OptimizationCollection = NULL;
        return TRUE;
    }

    // Optimizer callback is required
    if (Plugin ->OptimizePtr == NULL) return FALSE;

    fl = (_cmsOptimizationCollection*) _cmsPluginMalloc(ContextID, sizeof(_cmsOptimizationCollection));
    if (fl == NULL) return FALSE;

    // Copy the parameters
    fl ->OptimizePtr = Plugin ->OptimizePtr;

    // Keep linked list
    fl ->Next = ctx->OptimizationCollection;

    // Set the head
    ctx ->OptimizationCollection = fl;

    // All is ok
    return TRUE;
}