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
struct msg {int type; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  MSG_RSP_REDIS_ERROR_BUSY 130 
#define  MSG_RSP_REDIS_ERROR_LOADING 129 
#define  MSG_RSP_REDIS_ERROR_OOM 128 

bool
redis_failure(struct msg *r)
{
    ASSERT(!r->request);

    switch (r->type) {
    case MSG_RSP_REDIS_ERROR_OOM:
    case MSG_RSP_REDIS_ERROR_BUSY:
    case MSG_RSP_REDIS_ERROR_LOADING:
        return true;

    default:
        break;
    }

    return false;
}