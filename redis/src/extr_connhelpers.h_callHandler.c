#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ connection ;
typedef  int /*<<< orphan*/  (* ConnectionCallbackFunc ) (TYPE_1__*) ;

/* Variables and functions */
 int CONN_FLAG_CLOSE_SCHEDULED ; 
 int CONN_FLAG_IN_HANDLER ; 
 int /*<<< orphan*/  connClose (TYPE_1__*) ; 

__attribute__((used)) static inline int callHandler(connection *conn, ConnectionCallbackFunc handler) {
    conn->flags |= CONN_FLAG_IN_HANDLER;
    if (handler) handler(conn);
    conn->flags &= ~CONN_FLAG_IN_HANDLER;
    if (conn->flags & CONN_FLAG_CLOSE_SCHEDULED) {
        connClose(conn);
        return 0;
    }
    return 1;
}