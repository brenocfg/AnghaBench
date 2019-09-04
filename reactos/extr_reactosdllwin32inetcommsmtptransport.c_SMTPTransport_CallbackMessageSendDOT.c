#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pstmMsg; } ;
struct TYPE_4__ {int /*<<< orphan*/  InetTransport; TYPE_1__ pending_message; } ;
typedef  TYPE_2__ SMTPTransport ;
typedef  int /*<<< orphan*/  IInternetTransport ;

/* Variables and functions */
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InternetTransport_DoCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMTPTransport_CallbackMessageReadResponse ; 

__attribute__((used)) static void SMTPTransport_CallbackMessageSendDOT(IInternetTransport *iface, char *pBuffer, int cbBuffer)
{
    SMTPTransport *This = (SMTPTransport *)iface;

    IStream_Release(This->pending_message.pstmMsg);
    InternetTransport_DoCommand(&This->InetTransport, "\n.\n",
        SMTPTransport_CallbackMessageReadResponse);
}