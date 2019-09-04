#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hrServerError; } ;
struct TYPE_8__ {TYPE_1__ rIxpResult; } ;
struct TYPE_7__ {int /*<<< orphan*/  InetTransport; } ;
typedef  TYPE_2__ SMTPTransport ;
typedef  TYPE_3__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetTransport_DropConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMTPTransport_ParseResponse (TYPE_2__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 

__attribute__((used)) static void SMTPTransport_CallbackDisconnect(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    SMTPTransport *This = (SMTPTransport *)iface;
    SMTPRESPONSE response;
    HRESULT hr;

    TRACE("\n");

    if (pBuffer)
    {
        hr = SMTPTransport_ParseResponse(This, pBuffer, &response);
        if (FAILED(hr))
        {
            /* FIXME: handle error */
            return;
        }

        if (FAILED(response.rIxpResult.hrServerError))
        {
            ERR("server error: %s\n", debugstr_a(pBuffer));
            /* FIXME: handle error */
            return;
        }
    }
    InternetTransport_DropConnection(&This->InetTransport);
}