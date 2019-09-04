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
struct TYPE_3__ {int /*<<< orphan*/  cancel_event; int /*<<< orphan*/  sock_event; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ RpcConnection_tcp ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int FD_CLOSE ; 
 int FD_READ ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
#define  WAIT_OBJECT_0 128 
 scalar_t__ WSAEventSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int WaitForMultipleObjects (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL rpcrt4_sock_wait_for_recv(RpcConnection_tcp *tcpc)
{
  HANDLE wait_handles[2];
  DWORD res;
  if (WSAEventSelect(tcpc->sock, tcpc->sock_event, FD_READ | FD_CLOSE) == SOCKET_ERROR)
  {
    ERR("WSAEventSelect() failed with error %d\n", WSAGetLastError());
    return FALSE;
  }
  wait_handles[0] = tcpc->sock_event;
  wait_handles[1] = tcpc->cancel_event;
  res = WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE);
  switch (res)
  {
  case WAIT_OBJECT_0:
    return TRUE;
  case WAIT_OBJECT_0 + 1:
    return FALSE;
  default:
    ERR("WaitForMultipleObjects() failed with error %d\n", GetLastError());
    return FALSE;
  }
}