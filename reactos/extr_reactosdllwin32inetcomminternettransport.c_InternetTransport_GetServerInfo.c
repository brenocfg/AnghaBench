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
struct TYPE_3__ {scalar_t__ Status; int /*<<< orphan*/  ServerInfo; } ;
typedef  int /*<<< orphan*/ * LPINETSERVER ;
typedef  TYPE_1__ InternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ IXP_DISCONNECTED ; 
 int /*<<< orphan*/  IXP_E_NOT_CONNECTED ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT InternetTransport_GetServerInfo(InternetTransport *This, LPINETSERVER pInetServer)
{
    if (This->Status == IXP_DISCONNECTED)
        return IXP_E_NOT_CONNECTED;

    *pInetServer = This->ServerInfo;
    return S_OK;
}