#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * tls; } ;
struct vlc_h1_conn {int released; TYPE_1__ conn; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct vlc_h1_conn*) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tls_Shutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vlc_h1_conn_destroy(struct vlc_h1_conn *conn)
{
    assert(!conn->active);
    assert(conn->released);

    if (conn->conn.tls != NULL)
    {
        vlc_tls_Shutdown(conn->conn.tls, true);
        vlc_tls_Close(conn->conn.tls);
    }
    free(conn);
}