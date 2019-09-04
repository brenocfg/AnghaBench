#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  event_vector; } ;
typedef  TYPE_1__ HTMLDocumentNode ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int EVENTID_LAST ; 
 int EVENT_HASDEFAULTHANDLERS ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ensure_doc_nsevent_handler (TYPE_1__*,unsigned int) ; 
 TYPE_3__* event_info ; 
 int /*<<< orphan*/  heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_nsevents (TYPE_1__*) ; 

HRESULT doc_init_events(HTMLDocumentNode *doc)
{
    unsigned i;
    HRESULT hres;

    doc->event_vector = heap_alloc_zero(EVENTID_LAST*sizeof(BOOL));
    if(!doc->event_vector)
        return E_OUTOFMEMORY;

    init_nsevents(doc);

    for(i=0; i < EVENTID_LAST; i++) {
        if(event_info[i].flags & EVENT_HASDEFAULTHANDLERS) {
            hres = ensure_doc_nsevent_handler(doc, i);
            if(FAILED(hres))
                return hres;
        }
    }

    return S_OK;
}