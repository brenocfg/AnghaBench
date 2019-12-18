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
struct TYPE_3__ {int /*<<< orphan*/ * UnlockMutexPtr; int /*<<< orphan*/ * LockMutexPtr; int /*<<< orphan*/ * DestroyMutexPtr; int /*<<< orphan*/ * CreateMutexPtr; } ;
typedef  TYPE_1__ cmsPluginMutex ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_4__ {int /*<<< orphan*/ * UnlockMutexPtr; int /*<<< orphan*/ * LockMutexPtr; int /*<<< orphan*/ * DestroyMutexPtr; int /*<<< orphan*/ * CreateMutexPtr; } ;
typedef  TYPE_2__ _cmsMutexPluginChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MutexPlugin ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cmsBool  _cmsRegisterMutexPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    cmsPluginMutex* Plugin = (cmsPluginMutex*) Data;
    _cmsMutexPluginChunkType* ctx = ( _cmsMutexPluginChunkType*) _cmsContextGetClientChunk(ContextID, MutexPlugin);

    if (Data == NULL) {

        // No lock routines
        ctx->CreateMutexPtr = NULL;
        ctx->DestroyMutexPtr = NULL;
        ctx->LockMutexPtr = NULL;
        ctx ->UnlockMutexPtr = NULL;
        return TRUE;
    }

    // Factory callback is required
    if (Plugin ->CreateMutexPtr == NULL || Plugin ->DestroyMutexPtr == NULL ||
        Plugin ->LockMutexPtr == NULL || Plugin ->UnlockMutexPtr == NULL) return FALSE;


    ctx->CreateMutexPtr  = Plugin->CreateMutexPtr;
    ctx->DestroyMutexPtr = Plugin ->DestroyMutexPtr;
    ctx ->LockMutexPtr   = Plugin ->LockMutexPtr;
    ctx ->UnlockMutexPtr = Plugin ->UnlockMutexPtr;

    // All is ok
    return TRUE;
}