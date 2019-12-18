#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t i_headers; TYPE_1__* p_headers; } ;
typedef  TYPE_2__ httpd_message_t ;
struct TYPE_4__ {char const* value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

const char *httpd_MsgGet(const httpd_message_t *msg, const char *name)
{
    for (size_t i = 0; i < msg->i_headers; i++)
        if (!strcasecmp(msg->p_headers[i].name, name))
            return msg->p_headers[i].value;
    return NULL;
}