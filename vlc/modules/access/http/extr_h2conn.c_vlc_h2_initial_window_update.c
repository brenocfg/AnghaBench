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
typedef  scalar_t__ uint_fast32_t ;
typedef  scalar_t__ uint64_t ;
struct vlc_h2_stream {int /*<<< orphan*/  send_cwnd; struct vlc_h2_stream* older; } ;
struct vlc_h2_conn {struct vlc_h2_stream* streams; int /*<<< orphan*/  send_cwnd; scalar_t__ init_send_cwnd; } ;

/* Variables and functions */

__attribute__((used)) static void vlc_h2_initial_window_update(struct vlc_h2_conn *conn,
                                         uint_fast32_t value)
{
    uint64_t delta = (uint64_t)value - conn->init_send_cwnd;

    conn->init_send_cwnd = value;
    conn->send_cwnd += delta;

    for (struct vlc_h2_stream *s = conn->streams; s != NULL; s = s->older)
        s->send_cwnd += delta;
}