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
struct TYPE_3__ {int i_version; int /*<<< orphan*/ * p_body; scalar_t__ i_body; scalar_t__ i_body_offset; int /*<<< orphan*/ * p_headers; scalar_t__ i_headers; int /*<<< orphan*/ * psz_args; int /*<<< orphan*/ * psz_url; scalar_t__ i_status; int /*<<< orphan*/  i_proto; int /*<<< orphan*/  i_type; int /*<<< orphan*/ * cl; } ;
typedef  TYPE_1__ httpd_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  HTTPD_MSG_NONE ; 
 int /*<<< orphan*/  HTTPD_PROTO_NONE ; 

__attribute__((used)) static void httpd_MsgInit(httpd_message_t *msg)
{
    msg->cl         = NULL;
    msg->i_type     = HTTPD_MSG_NONE;
    msg->i_proto    = HTTPD_PROTO_NONE;
    msg->i_version  = -1; /* FIXME */

    msg->i_status   = 0;

    msg->psz_url    = NULL;
    msg->psz_args   = NULL;

    msg->i_headers  = 0;
    msg->p_headers  = NULL;

    msg->i_body_offset = 0;
    msg->i_body        = 0;
    msg->p_body        = NULL;
}