#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * xform; } ;
struct TYPE_6__ {int ExpectedVersion; } ;
struct TYPE_8__ {TYPE_2__ factories; TYPE_1__ base; } ;
typedef  TYPE_3__ cmsPluginTransform ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  void* cmsBool ;
struct TYPE_9__ {TYPE_5__* TransformCollection; } ;
typedef  TYPE_4__ _cmsTransformPluginChunkType ;
struct TYPE_10__ {struct TYPE_10__* Next; int /*<<< orphan*/ * Factory; void* OldXform; } ;
typedef  TYPE_5__ _cmsTransformCollection ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  TransformPlugin ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsPluginMalloc (int /*<<< orphan*/ ,int) ; 

cmsBool  _cmsRegisterTransformPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    cmsPluginTransform* Plugin = (cmsPluginTransform*) Data;
    _cmsTransformCollection* fl;
    _cmsTransformPluginChunkType* ctx = ( _cmsTransformPluginChunkType*) _cmsContextGetClientChunk(ContextID,TransformPlugin);

    if (Data == NULL) {

        // Free the chain. Memory is safely freed at exit
        ctx->TransformCollection = NULL;
        return TRUE;
    }

    // Factory callback is required
    if (Plugin->factories.xform == NULL) return FALSE;


    fl = (_cmsTransformCollection*) _cmsPluginMalloc(ContextID, sizeof(_cmsTransformCollection));
    if (fl == NULL) return FALSE;

    // Check for full xform plug-ins previous to 2.8, we would need an adapter in that case
    if (Plugin->base.ExpectedVersion < 2080) {

           fl->OldXform = TRUE;
    }
    else
           fl->OldXform = FALSE;

    // Copy the parameters
    fl->Factory = Plugin->factories.xform;

    // Keep linked list
    fl ->Next = ctx->TransformCollection;
    ctx->TransformCollection = fl;

    // All is ok
    return TRUE;
}