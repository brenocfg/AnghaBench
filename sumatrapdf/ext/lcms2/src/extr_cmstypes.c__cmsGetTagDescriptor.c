#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsTagDescriptor ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_4__ {TYPE_2__* Tag; } ;
typedef  TYPE_1__ _cmsTagPluginChunkType ;
struct TYPE_5__ {scalar_t__ Signature; int /*<<< orphan*/  Descriptor; struct TYPE_5__* Next; } ;
typedef  TYPE_2__ _cmsTagLinkedList ;

/* Variables and functions */
 TYPE_2__* SupportedTags ; 
 int /*<<< orphan*/  TagPlugin ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cmsTagDescriptor* _cmsGetTagDescriptor(cmsContext ContextID, cmsTagSignature sig)
{
    _cmsTagLinkedList* pt;
    _cmsTagPluginChunkType* TagPluginChunk = ( _cmsTagPluginChunkType*) _cmsContextGetClientChunk(ContextID, TagPlugin);

    for (pt = TagPluginChunk->Tag;
             pt != NULL;
             pt = pt ->Next) {

                if (sig == pt -> Signature) return &pt ->Descriptor;
    }

    for (pt = SupportedTags;
            pt != NULL;
            pt = pt ->Next) {

                if (sig == pt -> Signature) return &pt ->Descriptor;
    }

    return NULL;
}