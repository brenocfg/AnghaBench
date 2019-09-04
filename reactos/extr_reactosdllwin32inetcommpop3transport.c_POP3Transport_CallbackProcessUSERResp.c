#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pass ;
struct TYPE_6__ {char* szPassword; } ;
struct TYPE_8__ {TYPE_1__ ServerInfo; scalar_t__ pCallback; } ;
struct TYPE_7__ {TYPE_5__ InetTransport; } ;
typedef  TYPE_2__ POP3Transport ;
typedef  int /*<<< orphan*/  POP3RESPONSE ;
typedef  int /*<<< orphan*/  IPOP3Callback ;
typedef  int /*<<< orphan*/  IInternetTransport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPOP3Callback_OnResponse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InternetTransport_DoCommand (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POP3Transport_CallbackRecvPASSResp ; 
 int /*<<< orphan*/  POP3Transport_ParseResponse (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POP3_PASS ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  init_parser (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void POP3Transport_CallbackProcessUSERResp(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    static const char pass[] = "PASS ";
    POP3Transport *This = (POP3Transport *)iface;
    POP3RESPONSE response;
    char *command;
    int len;
    HRESULT hr;

    TRACE("\n");

    hr = POP3Transport_ParseResponse(This, pBuffer, &response);
    if (FAILED(hr))
    {
        /* FIXME: handle error */
        return;
    }

    IPOP3Callback_OnResponse((IPOP3Callback *)This->InetTransport.pCallback, &response);

    len = sizeof(pass) + strlen(This->InetTransport.ServerInfo.szPassword) + 2; /* "\r\n" */
    command = HeapAlloc(GetProcessHeap(), 0, len);

    strcpy(command, pass);
    strcat(command, This->InetTransport.ServerInfo.szPassword);
    strcat(command, "\r\n");

    init_parser(This, POP3_PASS);

    InternetTransport_DoCommand(&This->InetTransport, command, POP3Transport_CallbackRecvPASSResp);
    HeapFree(GetProcessHeap(), 0, command);
}