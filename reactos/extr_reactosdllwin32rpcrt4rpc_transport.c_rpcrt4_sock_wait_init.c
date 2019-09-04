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
typedef  int /*<<< orphan*/  WSADATA ;
struct TYPE_3__ {void* sock_event; void* cancel_event; } ;
typedef  TYPE_1__ RpcConnection_tcp ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (void*) ; 
 void* CreateEventW (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL rpcrt4_sock_wait_init(RpcConnection_tcp *tcpc)
{
  static BOOL wsa_inited;
  if (!wsa_inited)
  {
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    /* Note: WSAStartup can be called more than once so we don't bother with
     * making accesses to wsa_inited thread-safe */
    wsa_inited = TRUE;
  }
  tcpc->sock_event = CreateEventW(NULL, FALSE, FALSE, NULL);
  tcpc->cancel_event = CreateEventW(NULL, FALSE, FALSE, NULL);
  if (!tcpc->sock_event || !tcpc->cancel_event)
  {
    ERR("event creation failed\n");
    if (tcpc->sock_event) CloseHandle(tcpc->sock_event);
    return FALSE;
  }
  return TRUE;
}