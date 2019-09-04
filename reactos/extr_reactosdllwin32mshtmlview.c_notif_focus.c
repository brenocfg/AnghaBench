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
struct TYPE_3__ {int /*<<< orphan*/  focus; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  IOleControlSite ;
typedef  TYPE_1__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IOleControlSite ; 
 int /*<<< orphan*/  IOleClientSite_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleControlSite_OnFocus (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOleControlSite_Release (int /*<<< orphan*/ *) ; 

void notif_focus(HTMLDocumentObj *This)
{
    IOleControlSite *site;
    HRESULT hres;

    if(!This->client)
        return;

    hres = IOleClientSite_QueryInterface(This->client, &IID_IOleControlSite, (void**)&site);
    if(FAILED(hres))
        return;

    IOleControlSite_OnFocus(site, This->focus);
    IOleControlSite_Release(site);
}