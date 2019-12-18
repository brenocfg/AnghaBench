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
struct TYPE_2__ {int /*<<< orphan*/  tls; } ;
struct vlc_h2_conn {TYPE_1__ conn; int /*<<< orphan*/  out; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_H2_NO_ERROR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_h2_conn*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_error (struct vlc_h2_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_output_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_tls_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tls_Shutdown (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vlc_h2_conn_destroy(struct vlc_h2_conn *conn)
{
    assert(conn->streams == NULL);

    vlc_h2_error(conn, VLC_H2_NO_ERROR);

    vlc_cancel(conn->thread);
    vlc_join(conn->thread, NULL);
    vlc_mutex_destroy(&conn->lock);

    vlc_h2_output_destroy(conn->out);
    vlc_tls_Shutdown(conn->conn.tls, true);

    vlc_tls_Close(conn->conn.tls);
    free(conn);
}