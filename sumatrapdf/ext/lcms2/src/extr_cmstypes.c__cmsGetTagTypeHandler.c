#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsTagTypeSignature ;
typedef  int /*<<< orphan*/  cmsTagTypeHandler ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int /*<<< orphan*/  TagTypes; } ;
typedef  TYPE_1__ _cmsTagTypePluginChunkType ;
typedef  int /*<<< orphan*/  _cmsTagTypeLinkedList ;

/* Variables and functions */
 int /*<<< orphan*/ * GetHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SupportedTagTypes ; 
 int /*<<< orphan*/  TagTypePlugin ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cmsTagTypeHandler* _cmsGetTagTypeHandler(cmsContext ContextID, cmsTagTypeSignature sig)
{
    _cmsTagTypePluginChunkType* ctx = ( _cmsTagTypePluginChunkType*) _cmsContextGetClientChunk(ContextID, TagTypePlugin);

    return GetHandler(sig, ctx->TagTypes, (_cmsTagTypeLinkedList*) SupportedTagTypes);
}