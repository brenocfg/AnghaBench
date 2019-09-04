#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int update; scalar_t__ client; scalar_t__ hostui; int /*<<< orphan*/  hwnd; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  IOleCommandTarget ;
typedef  TYPE_1__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IDocHostUIHandler_UpdateUI (scalar_t__) ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IOleClientSite_QueryInterface (scalar_t__,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleCommandTarget_Exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCommandTarget_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OLECMDEXECOPT_DONTPROMPTUSER ; 
 int /*<<< orphan*/  OLECMDID_UPDATECOMMANDS ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_ID ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int) ; 
 int UPDATE_UI ; 
 int /*<<< orphan*/  update_title (TYPE_1__*) ; 

__attribute__((used)) static LRESULT on_timer(HTMLDocumentObj *This)
{
    TRACE("(%p) %x\n", This, This->update);

    KillTimer(This->hwnd, TIMER_ID);

    if(!This->update)
        return 0;

    if(This->update & UPDATE_UI) {
        if(This->hostui)
            IDocHostUIHandler_UpdateUI(This->hostui);

        if(This->client) {
            IOleCommandTarget *cmdtrg;
            HRESULT hres;

            hres = IOleClientSite_QueryInterface(This->client, &IID_IOleCommandTarget,
                                                 (void**)&cmdtrg);
            if(SUCCEEDED(hres)) {
                IOleCommandTarget_Exec(cmdtrg, NULL, OLECMDID_UPDATECOMMANDS,
                                       OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL);
                IOleCommandTarget_Release(cmdtrg);
            }
        }
    }

    update_title(This);
    This->update = 0;
    return 0;
}