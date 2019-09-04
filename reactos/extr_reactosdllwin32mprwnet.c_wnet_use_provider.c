#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct use_connection_context {int /*<<< orphan*/  (* set_accessname ) (struct use_connection_context*,int*) ;scalar_t__ accessname; int /*<<< orphan*/  userid; int /*<<< orphan*/  password; int /*<<< orphan*/  flags; int /*<<< orphan*/  hwndOwner; } ;
struct TYPE_7__ {scalar_t__ (* getCaps ) (int /*<<< orphan*/ ) ;scalar_t__ (* addConnection3 ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* addConnection ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ WNetProvider ;
struct TYPE_8__ {char* lpLocalName; } ;
typedef  TYPE_2__ NETRESOURCEW ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ ERROR_BAD_PROVIDER ; 
 int /*<<< orphan*/  WNNC_CONNECTION ; 
 scalar_t__ WNNC_CON_ADDCONNECTION ; 
 scalar_t__ WNNC_CON_ADDCONNECTION3 ; 
 scalar_t__ WN_ACCESS_DENIED ; 
 scalar_t__ WN_ALREADY_CONNECTED ; 
 scalar_t__ WN_SUCCESS ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct use_connection_context*,int*) ; 

__attribute__((used)) static DWORD wnet_use_provider( struct use_connection_context *ctxt, NETRESOURCEW * netres, WNetProvider *provider, BOOLEAN redirect )
{
    DWORD caps, ret;

    caps = provider->getCaps(WNNC_CONNECTION);
    if (!(caps & (WNNC_CON_ADDCONNECTION | WNNC_CON_ADDCONNECTION3)))
        return ERROR_BAD_PROVIDER;

    ret = WN_ACCESS_DENIED;
    do
    {
        if ((caps & WNNC_CON_ADDCONNECTION3) && provider->addConnection3)
            ret = provider->addConnection3(ctxt->hwndOwner, netres, ctxt->password, ctxt->userid, ctxt->flags);
        else if ((caps & WNNC_CON_ADDCONNECTION) && provider->addConnection)
            ret = provider->addConnection(netres, ctxt->password, ctxt->userid);

        if (ret == WN_ALREADY_CONNECTED && redirect)
            netres->lpLocalName[0] -= 1;
    } while (redirect && ret == WN_ALREADY_CONNECTED && netres->lpLocalName[0] >= 'C');

    if (ret == WN_SUCCESS && ctxt->accessname)
        ctxt->set_accessname(ctxt, netres->lpLocalName);

    return ret;
}