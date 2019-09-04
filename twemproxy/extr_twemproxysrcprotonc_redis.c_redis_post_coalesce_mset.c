#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msg {int error; int /*<<< orphan*/  err; struct msg* peer; } ;
typedef  scalar_t__ rstatus_t ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ msg_append (struct msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ rsp_ok ; 

void
redis_post_coalesce_mset(struct msg *request)
{
    rstatus_t status;
    struct msg *response = request->peer;

    status = msg_append(response, rsp_ok.data, rsp_ok.len);
    if (status != NC_OK) {
        response->error = 1;        /* mark this msg as err */
        response->err = errno;
    }
}