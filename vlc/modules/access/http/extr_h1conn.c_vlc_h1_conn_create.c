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
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct vlc_http_conn {int /*<<< orphan*/ * tls; int /*<<< orphan*/ * cbs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cbs; } ;
struct vlc_h1_conn {int active; int released; int proxy; struct vlc_http_conn conn; void* opaque; TYPE_1__ stream; } ;

/* Variables and functions */
 struct vlc_h1_conn* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h1_conn_callbacks ; 
 int /*<<< orphan*/  vlc_h1_stream_callbacks ; 

struct vlc_http_conn *vlc_h1_conn_create(void *ctx, vlc_tls_t *tls, bool proxy)
{
    struct vlc_h1_conn *conn = malloc(sizeof (*conn));
    if (unlikely(conn == NULL))
        return NULL;

    conn->conn.cbs = &vlc_h1_conn_callbacks;
    conn->conn.tls = tls;
    conn->stream.cbs = &vlc_h1_stream_callbacks;
    conn->active = false;
    conn->released = false;
    conn->proxy = proxy;
    conn->opaque = ctx;

    return &conn->conn;
}