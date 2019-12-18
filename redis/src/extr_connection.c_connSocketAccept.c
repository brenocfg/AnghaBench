#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; } ;
typedef  TYPE_1__ connection ;
typedef  int /*<<< orphan*/  ConnectionCallbackFunc ;

/* Variables and functions */
 scalar_t__ CONN_STATE_ACCEPTING ; 
 scalar_t__ CONN_STATE_CONNECTED ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  callHandler (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int connSocketAccept(connection *conn, ConnectionCallbackFunc accept_handler) {
    if (conn->state != CONN_STATE_ACCEPTING) return C_ERR;
    conn->state = CONN_STATE_CONNECTED;
    if (!callHandler(conn, accept_handler)) return C_ERR;
    return C_OK;
}