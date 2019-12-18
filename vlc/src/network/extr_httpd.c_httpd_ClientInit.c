#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_3__ {int i_keyframe_wait_to_pass; int b_stream_mode; int /*<<< orphan*/  answer; int /*<<< orphan*/  query; int /*<<< orphan*/  i_buffer_size; int /*<<< orphan*/  p_buffer; scalar_t__ i_buffer; int /*<<< orphan*/  i_activity_timeout; int /*<<< orphan*/  i_activity_date; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_1__ httpd_client_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_CLIENT_RECEIVING ; 
 int /*<<< orphan*/  HTTPD_CL_BUFSIZE ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  httpd_MsgInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void httpd_ClientInit(httpd_client_t *cl, vlc_tick_t now)
{
    cl->i_state = HTTPD_CLIENT_RECEIVING;
    cl->i_activity_date = now;
    cl->i_activity_timeout = VLC_TICK_FROM_SEC(10);
    cl->i_buffer_size = HTTPD_CL_BUFSIZE;
    cl->i_buffer = 0;
    cl->p_buffer = xmalloc(cl->i_buffer_size);
    cl->i_keyframe_wait_to_pass = -1;
    cl->b_stream_mode = false;

    httpd_MsgInit(&cl->query);
    httpd_MsgInit(&cl->answer);
}