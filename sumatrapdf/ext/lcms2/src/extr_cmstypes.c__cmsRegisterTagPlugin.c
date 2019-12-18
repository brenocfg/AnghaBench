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
struct TYPE_4__ {int /*<<< orphan*/  Descriptor; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_1__ cmsPluginTag ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_5__ {TYPE_3__* Tag; } ;
typedef  TYPE_2__ _cmsTagPluginChunkType ;
struct TYPE_6__ {struct TYPE_6__* Next; int /*<<< orphan*/  Descriptor; int /*<<< orphan*/  Signature; } ;
typedef  TYPE_3__ _cmsTagLinkedList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TagPlugin ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsPluginMalloc (int /*<<< orphan*/ ,int) ; 

cmsBool  _cmsRegisterTagPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    cmsPluginTag* Plugin = (cmsPluginTag*) Data;
    _cmsTagLinkedList *pt;
    _cmsTagPluginChunkType* TagPluginChunk = ( _cmsTagPluginChunkType*) _cmsContextGetClientChunk(ContextID, TagPlugin);

    if (Data == NULL) {

        TagPluginChunk->Tag = NULL;
        return TRUE;
    }

    pt = (_cmsTagLinkedList*) _cmsPluginMalloc(ContextID, sizeof(_cmsTagLinkedList));
    if (pt == NULL) return FALSE;

    pt ->Signature  = Plugin ->Signature;
    pt ->Descriptor = Plugin ->Descriptor;
    pt ->Next       = TagPluginChunk ->Tag;

    TagPluginChunk ->Tag = pt;

    return TRUE;
}