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
typedef  int uint32_t ;
struct vlc_h2_conn {int dummy; } ;

/* Variables and functions */
 scalar_t__ vlc_h2_conn_queue_prio (struct vlc_h2_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_frame_window_update (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vlc_h2_window_status(void *ctx, uint32_t *restrict rcwd)
{
    struct vlc_h2_conn *conn = ctx;

    /* Maintain connection receive window to insanely large values.
     * Congestion control is done per stream instead. */
    if (*rcwd < (1 << 30)
     && vlc_h2_conn_queue_prio(conn,
                               vlc_h2_frame_window_update(0, 1 << 30)) == 0)
        *rcwd += 1 << 30;
}