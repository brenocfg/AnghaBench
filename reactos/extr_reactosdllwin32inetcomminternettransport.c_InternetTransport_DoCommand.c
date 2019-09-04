#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vtbl; } ;
struct TYPE_6__ {scalar_t__ Status; TYPE_1__ u; scalar_t__ pCallback; scalar_t__ fCommandLogging; scalar_t__ fnCompletion; } ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  scalar_t__ LPCSTR ;
typedef  TYPE_2__ InternetTransport ;
typedef  int /*<<< orphan*/  INETXPORT_COMPLETION_FUNCTION ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND ; 
 int /*<<< orphan*/  ITransportCallback_OnCommand (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IXP_DISCONNECTED ; 
 int /*<<< orphan*/  IXP_E_BUSY ; 
 int /*<<< orphan*/  IXP_E_NOT_CONNECTED ; 
 int /*<<< orphan*/  InternetTransport_Write (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

HRESULT InternetTransport_DoCommand(InternetTransport *This,
    LPCSTR pszCommand, INETXPORT_COMPLETION_FUNCTION fnCompletion)
{
    if (This->Status == IXP_DISCONNECTED)
        return IXP_E_NOT_CONNECTED;

    if (This->fnCompletion)
        return IXP_E_BUSY;

    if (This->pCallback && This->fCommandLogging)
    {
        ITransportCallback_OnCommand(This->pCallback, CMD_SEND, (LPSTR)pszCommand, 0,
            (IInternetTransport *)&This->u.vtbl);
    }
    return InternetTransport_Write(This, pszCommand, strlen(pszCommand), fnCompletion);
}