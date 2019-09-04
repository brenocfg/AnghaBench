#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hrServerError; } ;
struct TYPE_11__ {TYPE_1__ rIxpResult; int /*<<< orphan*/  command; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {scalar_t__ pCallback; } ;
struct TYPE_10__ {TYPE_2__ InetTransport; } ;
typedef  TYPE_3__ SMTPTransport ;
typedef  TYPE_4__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  ISMTPCallback ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISMTPCallback_OnResponse (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  SMTPTransport_ParseResponse (TYPE_3__*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  SMTP_DATA ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 

__attribute__((used)) static void SMTPTransport_CallbackProcessDATAResponse(IInternetTransport *iface, char *pBuffer, int cbBuffer)
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

    response.command = SMTP_DATA;
    ISMTPCallback_OnResponse((ISMTPCallback *)This->InetTransport.pCallback, &response);

    if (FAILED(response.rIxpResult.hrServerError))
    {
        ERR("server error: %s\n", debugstr_a(pBuffer));
        /* FIXME: handle error */
        return;
    }
}