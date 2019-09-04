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
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__* event_vector; } ;
typedef  TYPE_1__ HTMLDocumentNode ;

/* Variables and functions */
 int EVENTID_LAST ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  detach_nsevent (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* event_info ; 
 int /*<<< orphan*/  release_nsevents (TYPE_1__*) ; 

void detach_events(HTMLDocumentNode *doc)
{
    if(doc->event_vector) {
        int i;

        for(i=0; i < EVENTID_LAST; i++) {
            if(doc->event_vector[i]) {
                detach_nsevent(doc, event_info[i].name);
                doc->event_vector[i] = FALSE;
            }
        }
    }

    release_nsevents(doc);
}