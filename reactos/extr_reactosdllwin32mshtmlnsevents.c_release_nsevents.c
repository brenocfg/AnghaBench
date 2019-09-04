#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * doc; int /*<<< orphan*/  load_listener; int /*<<< orphan*/  keypress_listener; int /*<<< orphan*/  focus_listener; int /*<<< orphan*/  blur_listener; } ;
typedef  TYPE_1__ nsDocumentEventListener ;
struct TYPE_9__ {TYPE_1__* nsevent_listener; } ;
typedef  TYPE_2__ HTMLDocumentNode ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  blurW ; 
 int /*<<< orphan*/  detach_nslistener (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  focusW ; 
 int /*<<< orphan*/  keypressW ; 
 int /*<<< orphan*/  loadW ; 
 int /*<<< orphan*/  release_listener (TYPE_1__*) ; 

void release_nsevents(HTMLDocumentNode *doc)
{
    nsDocumentEventListener *listener = doc->nsevent_listener;

    TRACE("%p %p\n", doc, doc->nsevent_listener);

    if(!listener)
        return;

    detach_nslistener(doc, blurW,     &listener->blur_listener,     TRUE);
    detach_nslistener(doc, focusW,    &listener->focus_listener,    TRUE);
    detach_nslistener(doc, keypressW, &listener->keypress_listener, FALSE);
    detach_nslistener(doc, loadW,     &listener->load_listener,     TRUE);

    listener->doc = NULL;
    release_listener(listener);
    doc->nsevent_listener = NULL;
}