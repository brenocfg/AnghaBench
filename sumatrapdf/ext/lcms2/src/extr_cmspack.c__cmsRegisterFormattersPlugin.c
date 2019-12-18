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
struct TYPE_4__ {int /*<<< orphan*/  FormattersFactory; } ;
typedef  TYPE_1__ cmsPluginFormatters ;
typedef  int /*<<< orphan*/  cmsPluginBase ;
struct TYPE_5__ {struct TYPE_5__* Next; int /*<<< orphan*/  Factory; } ;
typedef  TYPE_2__ cmsFormattersFactoryList ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_6__ {TYPE_2__* FactoryList; } ;
typedef  TYPE_3__ _cmsFormattersPluginChunkType ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FormattersPlugin ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsPluginMalloc (int /*<<< orphan*/ ,int) ; 

cmsBool  _cmsRegisterFormattersPlugin(cmsContext ContextID, cmsPluginBase* Data)
{
    _cmsFormattersPluginChunkType* ctx = ( _cmsFormattersPluginChunkType*) _cmsContextGetClientChunk(ContextID, FormattersPlugin);
    cmsPluginFormatters* Plugin = (cmsPluginFormatters*) Data;
    cmsFormattersFactoryList* fl ;

    // Reset to built-in defaults
    if (Data == NULL) {

          ctx ->FactoryList = NULL;
          return TRUE;
    }

    fl = (cmsFormattersFactoryList*) _cmsPluginMalloc(ContextID, sizeof(cmsFormattersFactoryList));
    if (fl == NULL) return FALSE;

    fl ->Factory    = Plugin ->FormattersFactory;

    fl ->Next = ctx -> FactoryList;
    ctx ->FactoryList = fl;

    return TRUE;
}