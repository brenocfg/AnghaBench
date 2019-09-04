#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* window_ref; } ;
typedef  TYPE_2__ nsWineURI ;
struct TYPE_14__ {TYPE_3__* window; } ;
struct TYPE_13__ {TYPE_1__* doc_obj; TYPE_4__* window_ref; } ;
struct TYPE_11__ {int /*<<< orphan*/  nscontainer; } ;
typedef  TYPE_3__ HTMLOuterWindow ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  set_uri_nscontainer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowref_addref (TYPE_4__*) ; 
 int /*<<< orphan*/  windowref_release (TYPE_4__*) ; 

__attribute__((used)) static void set_uri_window(nsWineURI *This, HTMLOuterWindow *window)
{
    if(This->window_ref) {
        if(This->window_ref->window == window)
            return;
        TRACE("Changing %p -> %p\n", This->window_ref->window, window);
        windowref_release(This->window_ref);
    }

    if(window) {
        windowref_addref(window->window_ref);
        This->window_ref = window->window_ref;

        if(window->doc_obj)
            set_uri_nscontainer(This, window->doc_obj->nscontainer);
    }else {
        This->window_ref = NULL;
    }
}