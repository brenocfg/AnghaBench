#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ httpd_redirect_t ;
struct TYPE_9__ {int i_version; int i_status; unsigned char* p_body; int /*<<< orphan*/  i_body; int /*<<< orphan*/  i_type; int /*<<< orphan*/  i_proto; } ;
typedef  TYPE_2__ httpd_message_t ;
struct TYPE_10__ {int /*<<< orphan*/  query; } ;
typedef  TYPE_3__ httpd_client_t ;
typedef  int /*<<< orphan*/  httpd_callback_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_MSG_ANSWER ; 
 int /*<<< orphan*/  HTTPD_PROTO_HTTP ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  httpd_HtmlError (char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  httpd_MsgAdd (TYPE_2__*,char*,char*,...) ; 
 int /*<<< orphan*/ * httpd_MsgGet (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int httpd_RedirectCallBack(httpd_callback_sys_t *p_sys,
                                   httpd_client_t *cl, httpd_message_t *answer,
                                   const httpd_message_t *query)
{
    httpd_redirect_t *rdir = (httpd_redirect_t*)p_sys;
    char *p_body;
    (void)cl;

    if (!answer || !query)
        return VLC_SUCCESS;

    answer->i_proto  = HTTPD_PROTO_HTTP;
    answer->i_version= 1;
    answer->i_type   = HTTPD_MSG_ANSWER;
    answer->i_status = 301;

    answer->i_body = httpd_HtmlError (&p_body, 301, rdir->dst);
    answer->p_body = (unsigned char *)p_body;

    /* XXX check if it's ok or we need to set an absolute url */
    httpd_MsgAdd(answer, "Location",  "%s", rdir->dst);

    httpd_MsgAdd(answer, "Content-Length", "%d", answer->i_body);

    if (httpd_MsgGet(&cl->query, "Connection") != NULL)
        httpd_MsgAdd(answer, "Connection", "close");

    return VLC_SUCCESS;
}