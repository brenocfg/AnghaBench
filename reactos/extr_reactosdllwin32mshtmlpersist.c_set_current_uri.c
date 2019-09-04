#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * url; int /*<<< orphan*/ * uri_nofrag; int /*<<< orphan*/ * uri; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  TYPE_1__ HTMLOuterWindow ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IUri_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_GetDisplayUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_uri_nofrag (int /*<<< orphan*/ *) ; 

void set_current_uri(HTMLOuterWindow *window, IUri *uri)
{
    if(window->uri) {
        IUri_Release(window->uri);
        window->uri = NULL;
    }

    if(window->uri_nofrag) {
        IUri_Release(window->uri_nofrag);
        window->uri_nofrag = NULL;
    }

    SysFreeString(window->url);
    window->url = NULL;

    if(!uri)
        return;

    IUri_AddRef(uri);
    window->uri = uri;

    window->uri_nofrag = get_uri_nofrag(uri);
    if(!window->uri_nofrag) {
        FIXME("get_uri_nofrag failed\n");
        IUri_AddRef(uri);
        window->uri_nofrag = uri;
    }

    IUri_GetDisplayUri(uri, &window->url);
}