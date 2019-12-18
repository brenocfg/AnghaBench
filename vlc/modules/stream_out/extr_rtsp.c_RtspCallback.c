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
typedef  int /*<<< orphan*/  rtsp_stream_t ;
typedef  int /*<<< orphan*/  httpd_message_t ;
typedef  int /*<<< orphan*/  httpd_client_t ;
typedef  int /*<<< orphan*/  httpd_callback_sys_t ;

/* Variables and functions */
 int RtspHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int RtspCallback( httpd_callback_sys_t *p_args,
                         httpd_client_t *cl,
                         httpd_message_t *answer,
                         const httpd_message_t *query )
{
    return RtspHandler( (rtsp_stream_t *)p_args, NULL, cl, answer, query );
}