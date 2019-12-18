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
struct vlc_tls {int dummy; } ;
struct vlc_http_conn {struct vlc_tls* tls; int /*<<< orphan*/ * cbs; } ;
struct vlc_h2_conn {int next_id; int released; struct vlc_http_conn conn; int /*<<< orphan*/ * out; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; void* send_cwnd; void* init_send_cwnd; int /*<<< orphan*/ * streams; void* opaque; } ;

/* Variables and functions */
 void* VLC_H2_DEFAULT_INIT_WINDOW ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_INPUT ; 
 int /*<<< orphan*/  free (struct vlc_h2_conn*) ; 
 struct vlc_h2_conn* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vlc_h2_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_conn_callbacks ; 
 scalar_t__ vlc_h2_conn_queue (struct vlc_h2_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_frame_settings () ; 
 int /*<<< orphan*/ * vlc_h2_output_create (struct vlc_tls*,int) ; 
 int /*<<< orphan*/  vlc_h2_output_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_h2_recv_thread ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

struct vlc_http_conn *vlc_h2_conn_create(void *ctx, struct vlc_tls *tls)
{
    struct vlc_h2_conn *conn = malloc(sizeof (*conn));
    if (unlikely(conn == NULL))
        return NULL;

    conn->conn.cbs = &vlc_h2_conn_callbacks;
    conn->conn.tls = tls;
    conn->out = vlc_h2_output_create(tls, true);
    conn->opaque = ctx;
    conn->streams = NULL;
    conn->next_id = 1; /* TODO: server side */
    conn->released = false;
    conn->init_send_cwnd = VLC_H2_DEFAULT_INIT_WINDOW;
    conn->send_cwnd = VLC_H2_DEFAULT_INIT_WINDOW;

    if (unlikely(conn->out == NULL))
        goto error;

    vlc_mutex_init(&conn->lock);

    if (vlc_h2_conn_queue(conn, vlc_h2_frame_settings())
     || vlc_clone(&conn->thread, vlc_h2_recv_thread, conn,
                  VLC_THREAD_PRIORITY_INPUT))
    {
        vlc_mutex_destroy(&conn->lock);
        vlc_h2_output_destroy(conn->out);
        goto error;
    }
    return &conn->conn;
error:
    free(conn);
    return NULL;
}