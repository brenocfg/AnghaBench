#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _cmsContext_struct {int /*<<< orphan*/  DefaultMemoryManager; void** chunks; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ReallocPtr; int /*<<< orphan*/ * FreePtr; int /*<<< orphan*/ * MallocPtr; } ;
typedef  TYPE_1__ cmsPluginMemHandler ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/ * cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  _cmsMemPluginChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t MemPlugin ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  _cmsInstallAllocFunctions (TYPE_1__*,int /*<<< orphan*/ *) ; 

cmsBool  _cmsRegisterMemHandlerPlugin(cmsContext ContextID, cmsPluginBase *Data)
{
    cmsPluginMemHandler* Plugin = (cmsPluginMemHandler*) Data;
    _cmsMemPluginChunkType* ptr;

    // NULL forces to reset to defaults. In this special case, the defaults are stored in the context structure.
    // Remaining plug-ins does NOT have any copy in the context structure, but this is somehow special as the
    // context internal data should be malloce'd by using those functions.
    if (Data == NULL) {

       struct _cmsContext_struct* ctx = ( struct _cmsContext_struct*) ContextID;

       // Return to the default allocators
        if (ContextID != NULL) {
            ctx->chunks[MemPlugin] = (void*) &ctx->DefaultMemoryManager;
        }
        return TRUE;
    }

    // Check for required callbacks
    if (Plugin -> MallocPtr == NULL ||
        Plugin -> FreePtr == NULL ||
        Plugin -> ReallocPtr == NULL) return FALSE;

    // Set replacement functions
    ptr = (_cmsMemPluginChunkType*) _cmsContextGetClientChunk(ContextID, MemPlugin);
    if (ptr == NULL)
        return FALSE;

    _cmsInstallAllocFunctions(Plugin, ptr);
    return TRUE;
}