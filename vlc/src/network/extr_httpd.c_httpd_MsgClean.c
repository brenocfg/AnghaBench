#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t i_headers; TYPE_4__* p_body; TYPE_4__* p_headers; TYPE_4__* psz_args; TYPE_4__* psz_url; } ;
typedef  TYPE_1__ httpd_message_t ;
struct TYPE_6__ {struct TYPE_6__* value; struct TYPE_6__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  httpd_MsgInit (TYPE_1__*) ; 

__attribute__((used)) static void httpd_MsgClean(httpd_message_t *msg)
{
    free(msg->psz_url);
    free(msg->psz_args);
    for (size_t i = 0; i < msg->i_headers; i++) {
        free(msg->p_headers[i].name);
        free(msg->p_headers[i].value);
    }
    free(msg->p_headers);
    free(msg->p_body);
    httpd_MsgInit(msg);
}