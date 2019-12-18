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
struct vlc_h2_stream {int interrupted; int /*<<< orphan*/  recv_wait; struct vlc_h2_conn* conn; } ;
struct vlc_h2_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_h2_stream_wake_up(void *data)
{
    struct vlc_h2_stream *s = data;
    struct vlc_h2_conn *conn = s->conn;

    vlc_mutex_lock(&conn->lock);
    s->interrupted = true;
    vlc_cond_signal(&s->recv_wait);
    vlc_mutex_unlock(&conn->lock);
}