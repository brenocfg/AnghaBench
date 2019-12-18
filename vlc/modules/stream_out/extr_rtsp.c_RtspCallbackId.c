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
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ rtsp_stream_id_t ;
typedef  int /*<<< orphan*/  httpd_message_t ;
typedef  int /*<<< orphan*/  httpd_client_t ;
typedef  int /*<<< orphan*/  httpd_callback_sys_t ;

/* Variables and functions */
 int RtspHandler (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int RtspCallbackId( httpd_callback_sys_t *p_args,
                           httpd_client_t *cl,
                           httpd_message_t *answer,
                           const httpd_message_t *query )
{
    rtsp_stream_id_t *id = (rtsp_stream_id_t *)p_args;
    return RtspHandler( id->stream, id, cl, answer, query );
}