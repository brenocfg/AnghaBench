#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* window; int /*<<< orphan*/  cp_container; } ;
struct TYPE_10__ {scalar_t__ usermode; TYPE_5__ basedoc; int /*<<< orphan*/  doc_object_service; scalar_t__ webbrowser; scalar_t__ view_sink; } ;
struct TYPE_8__ {int /*<<< orphan*/  IHTMLWindow2_iface; } ;
struct TYPE_9__ {int load_flags; TYPE_1__ base; } ;
typedef  TYPE_3__ HTMLDocumentObj ;

/* Variables and functions */
 int BINDING_REFRESH ; 
 int /*<<< orphan*/  DVASPECT_CONTENT ; 
 scalar_t__ EDITMODE ; 
 int /*<<< orphan*/  IAdviseSink_OnViewChange (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDocObjectService_FireNavigateComplete2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  call_explorer_69 (TYPE_3__*) ; 
 int /*<<< orphan*/  call_property_onchanged (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_editor (TYPE_5__*) ; 

__attribute__((used)) static void parse_complete(HTMLDocumentObj *doc)
{
    TRACE("(%p)\n", doc);

    if(doc->usermode == EDITMODE)
        init_editor(&doc->basedoc);

    call_explorer_69(doc);
    if(doc->view_sink)
        IAdviseSink_OnViewChange(doc->view_sink, DVASPECT_CONTENT, -1);
    call_property_onchanged(&doc->basedoc.cp_container, 1005);
    call_explorer_69(doc);

    if(doc->webbrowser && doc->usermode != EDITMODE && !(doc->basedoc.window->load_flags & BINDING_REFRESH))
        IDocObjectService_FireNavigateComplete2(doc->doc_object_service, &doc->basedoc.window->base.IHTMLWindow2_iface, 0);

    /* FIXME: IE7 calls EnableModelless(TRUE), EnableModelless(FALSE) and sets interactive state here */
}