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
struct msg {int error; int /*<<< orphan*/  err; int /*<<< orphan*/  integer; struct msg* peer; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ msg_prepend_format (struct msg*,char*,int /*<<< orphan*/ ) ; 

void
redis_post_coalesce_del(struct msg *request)
{
    struct msg *response = request->peer;
    rstatus_t status;

    status = msg_prepend_format(response, ":%d\r\n", request->integer);
    if (status != NC_OK) {
        response->error = 1;
        response->err = errno;
    }
}