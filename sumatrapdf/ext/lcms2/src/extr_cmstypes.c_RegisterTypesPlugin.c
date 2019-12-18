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
struct TYPE_4__ {int /*<<< orphan*/  Handler; } ;
typedef  TYPE_1__ cmsPluginTagType ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {TYPE_3__* TagTypes; } ;
typedef  TYPE_2__ _cmsTagTypePluginChunkType ;
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/  Handler; } ;
typedef  TYPE_3__ _cmsTagTypeLinkedList ;
typedef  int /*<<< orphan*/  _cmsMemoryClient ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsPluginMalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsBool RegisterTypesPlugin(cmsContext ContextID, cmsPluginBase* Data, _cmsMemoryClient pos)
{
    cmsPluginTagType* Plugin = (cmsPluginTagType*) Data;
    _cmsTagTypePluginChunkType* ctx = ( _cmsTagTypePluginChunkType*) _cmsContextGetClientChunk(ContextID, pos);
    _cmsTagTypeLinkedList *pt;

    // Calling the function with NULL as plug-in would unregister the plug in.
    if (Data == NULL) {

        // There is no need to set free the memory, as pool is destroyed as a whole.
        ctx ->TagTypes = NULL;
        return TRUE;
    }

    // Registering happens in plug-in memory pool.
    pt = (_cmsTagTypeLinkedList*) _cmsPluginMalloc(ContextID, sizeof(_cmsTagTypeLinkedList));
    if (pt == NULL) return FALSE;

    pt ->Handler   = Plugin ->Handler;
    pt ->Next      = ctx ->TagTypes;

    ctx ->TagTypes = pt;

    return TRUE;
}