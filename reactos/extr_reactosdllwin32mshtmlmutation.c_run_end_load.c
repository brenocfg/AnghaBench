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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsISupports ;
struct TYPE_8__ {TYPE_3__* doc_node; } ;
struct TYPE_11__ {TYPE_1__ basedoc; } ;
struct TYPE_9__ {int /*<<< orphan*/  window; TYPE_5__* doc_obj; } ;
struct TYPE_10__ {TYPE_2__ basedoc; } ;
typedef  TYPE_3__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  READYSTATE_INTERACTIVE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  bind_event_scripts (TYPE_3__*) ; 
 int /*<<< orphan*/  parse_complete (TYPE_5__*) ; 
 int /*<<< orphan*/  set_ready_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static nsresult run_end_load(HTMLDocumentNode *This, nsISupports *arg1, nsISupports *arg2)
{
    TRACE("(%p)\n", This);

    if(!This->basedoc.doc_obj)
        return NS_OK;

    if(This == This->basedoc.doc_obj->basedoc.doc_node) {
        /*
         * This should be done in the worker thread that parses HTML,
         * but we don't have such thread (Gecko parses HTML for us).
         */
        parse_complete(This->basedoc.doc_obj);
    }

    bind_event_scripts(This);
    set_ready_state(This->basedoc.window, READYSTATE_INTERACTIVE);
    return NS_OK;
}