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
struct vlc_h1_conn {TYPE_1__ conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CO (struct vlc_h1_conn*) ; 
 int /*<<< orphan*/  vlc_http_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tls_Shutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *vlc_h1_stream_fatal(struct vlc_h1_conn *conn)
{
    if (conn->conn.tls != NULL)
    {
        vlc_http_dbg(CO(conn), "connection failed");
        vlc_tls_Shutdown(conn->conn.tls, true);
        vlc_tls_Close(conn->conn.tls);
        conn->conn.tls = NULL;
    }
    return NULL;
}