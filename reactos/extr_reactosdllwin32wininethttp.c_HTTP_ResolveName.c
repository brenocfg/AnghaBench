#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int addr_len; int /*<<< orphan*/  addr_str; int /*<<< orphan*/  name; int /*<<< orphan*/  addr; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ server_t ;
struct TYPE_7__ {int /*<<< orphan*/  dwContext; } ;
struct TYPE_6__ {TYPE_3__ hdr; TYPE_1__* server; TYPE_1__* proxy; } ;
typedef  TYPE_2__ http_request_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SOCKADDR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_STATUS_NAME_RESOLVED ; 
 int /*<<< orphan*/  INTERNET_STATUS_RESOLVING_NAME ; 
 int /*<<< orphan*/  INTERNET_SendCallback (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD HTTP_ResolveName(http_request_t *request)
{
    server_t *server = request->proxy ? request->proxy : request->server;
    int addr_len;

    if(server->addr_len)
        return ERROR_SUCCESS;

    INTERNET_SendCallback(&request->hdr, request->hdr.dwContext,
                          INTERNET_STATUS_RESOLVING_NAME,
                          server->name,
                          (strlenW(server->name)+1) * sizeof(WCHAR));

    addr_len = sizeof(server->addr);
    if (!GetAddress(server->name, server->port, (SOCKADDR*)&server->addr, &addr_len, server->addr_str))
        return ERROR_INTERNET_NAME_NOT_RESOLVED;

    server->addr_len = addr_len;
    INTERNET_SendCallback(&request->hdr, request->hdr.dwContext,
                          INTERNET_STATUS_NAME_RESOLVED,
                          server->addr_str, strlen(server->addr_str)+1);

    TRACE("resolved %s to %s\n", debugstr_w(server->name), server->addr_str);
    return ERROR_SUCCESS;
}