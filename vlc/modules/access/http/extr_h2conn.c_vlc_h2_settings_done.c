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
struct vlc_h2_conn {int dummy; } ;

/* Variables and functions */
 int vlc_h2_conn_queue (struct vlc_h2_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_h2_frame_settings_ack () ; 

__attribute__((used)) static int vlc_h2_settings_done(void *ctx)
{
    struct vlc_h2_conn *conn = ctx;

    return vlc_h2_conn_queue(conn, vlc_h2_frame_settings_ack());
}