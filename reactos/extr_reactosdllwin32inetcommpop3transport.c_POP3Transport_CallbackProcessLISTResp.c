#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ pCallback; } ;
struct TYPE_8__ {int /*<<< orphan*/  fDone; } ;
struct TYPE_7__ {TYPE_5__ InetTransport; } ;
typedef  TYPE_1__ POP3Transport ;
typedef  TYPE_2__ POP3RESPONSE ;
typedef  int /*<<< orphan*/  IPOP3Callback ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPOP3Callback_OnResponse (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  InternetTransport_ReadLine (TYPE_5__*,void (*) (int /*<<< orphan*/ *,char*,int)) ; 
 int /*<<< orphan*/  POP3Transport_ParseResponse (TYPE_1__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 

__attribute__((used)) static void POP3Transport_CallbackProcessLISTResp(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    POP3Transport *This = (POP3Transport *)iface;
    POP3RESPONSE response;
    HRESULT hr;

    TRACE("\n");

    hr = POP3Transport_ParseResponse(This, pBuffer, &response);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }

    IPOP3Callback_OnResponse((IPOP3Callback *)This->InetTransport.pCallback, &response);

    if (!response.fDone)
    {
        InternetTransport_ReadLine(&This->InetTransport, POP3Transport_CallbackProcessLISTResp);
        return;
    }

    IPOP3Callback_OnResponse((IPOP3Callback *)This->InetTransport.pCallback, &response);
}