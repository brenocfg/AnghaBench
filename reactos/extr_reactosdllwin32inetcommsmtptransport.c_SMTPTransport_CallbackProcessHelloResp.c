#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  response ;
struct TYPE_13__ {scalar_t__ pCallback; } ;
struct TYPE_10__ {int /*<<< orphan*/  hrServerError; } ;
struct TYPE_12__ {scalar_t__ fDone; int /*<<< orphan*/  command; TYPE_1__ rIxpResult; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {TYPE_7__ InetTransport; scalar_t__ fESMTP; } ;
typedef  TYPE_2__ SMTPTransport ;
typedef  TYPE_3__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  ISMTPCallback ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISMTPCallback_OnResponse (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  IXP_AUTHORIZED ; 
 int /*<<< orphan*/  IXP_CONNECTED ; 
 int /*<<< orphan*/  InternetTransport_ChangeStatus (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetTransport_ReadLine (TYPE_7__*,void (*) (int /*<<< orphan*/ *,char*,int)) ; 
 int /*<<< orphan*/  SMTPTransport_ParseResponse (TYPE_2__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  SMTP_CONNECTED ; 
 int /*<<< orphan*/  SMTP_EHLO ; 
 int /*<<< orphan*/  SMTP_HELO ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void SMTPTransport_CallbackProcessHelloResp(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    SMTPTransport *This = (SMTPTransport *)iface;
    SMTPRESPONSE response = { 0 };
    HRESULT hr;

    TRACE("\n");

    hr = SMTPTransport_ParseResponse(This, pBuffer, &response);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }

    response.command = This->fESMTP ? SMTP_EHLO : SMTP_HELO;
    ISMTPCallback_OnResponse((ISMTPCallback *)This->InetTransport.pCallback, &response);

    if (FAILED(response.rIxpResult.hrServerError))
    {
        ERR("server error: %s\n", debugstr_a(pBuffer));
        /* FIXME: handle error */
        return;
    }

    if (!response.fDone)
    {
        InternetTransport_ReadLine(&This->InetTransport,
            SMTPTransport_CallbackProcessHelloResp);
        return;
    }

    /* FIXME: try to authorize */

    /* always changed to this status, even if authorization not support on server */
    InternetTransport_ChangeStatus(&This->InetTransport, IXP_AUTHORIZED);
    InternetTransport_ChangeStatus(&This->InetTransport, IXP_CONNECTED);

    memset(&response, 0, sizeof(response));
    response.command = SMTP_CONNECTED;
    response.fDone = TRUE;
    ISMTPCallback_OnResponse((ISMTPCallback *)This->InetTransport.pCallback, &response);
}