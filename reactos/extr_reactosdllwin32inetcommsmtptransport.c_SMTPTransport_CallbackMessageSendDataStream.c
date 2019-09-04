#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  hrServerError; } ;
struct TYPE_10__ {TYPE_1__ rIxpResult; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbSize; int /*<<< orphan*/  pstmMsg; } ;
struct TYPE_9__ {int /*<<< orphan*/  InetTransport; TYPE_2__ pending_message; } ;
typedef  TYPE_3__ SMTPTransport ;
typedef  TYPE_4__ SMTPRESPONSE ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IStream_Read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetTransport_Write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMTPTransport_CallbackMessageSendDOT ; 
 int /*<<< orphan*/  SMTPTransport_ParseResponse (TYPE_3__*,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 

__attribute__((used)) static void SMTPTransport_CallbackMessageSendDataStream(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    SMTPTransport *This = (SMTPTransport *)iface;
    SMTPRESPONSE response;
    HRESULT hr;
    char *pszBuffer;
    ULONG cbSize;

    TRACE("\n");

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

    pszBuffer = HeapAlloc(GetProcessHeap(), 0, This->pending_message.cbSize);
    hr = IStream_Read(This->pending_message.pstmMsg, pszBuffer, This->pending_message.cbSize, NULL);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }
    cbSize = This->pending_message.cbSize;

    /* FIXME: map "\n.\n" to "\n..\n", reallocate memory, update cbSize */

    /* FIXME: properly stream the message rather than writing it all at once */

    hr = InternetTransport_Write(&This->InetTransport, pszBuffer, cbSize,
        SMTPTransport_CallbackMessageSendDOT);

    HeapFree(GetProcessHeap(), 0, pszBuffer);
}