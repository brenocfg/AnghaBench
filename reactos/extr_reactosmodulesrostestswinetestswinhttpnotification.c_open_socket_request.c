#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct test_request {int dummy; } ;
struct info {int dummy; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_async_request (int,struct test_request*,struct info*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_socket_available ; 
 int /*<<< orphan*/  server_socket_done ; 

__attribute__((used)) static void open_socket_request(int port, struct test_request *req, struct info *info)
{
    static const WCHAR socketW[] = {'/','s','o','c','k','e','t',0};

    ResetEvent( server_socket_done );
    open_async_request( port, req, info, socketW, FALSE );
    WaitForSingleObject( server_socket_available, INFINITE );
}