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
struct msg {int type; } ;

/* Variables and functions */
#define  MSG_REQ_MC_ADD 133 
#define  MSG_REQ_MC_APPEND 132 
#define  MSG_REQ_MC_CAS 131 
#define  MSG_REQ_MC_PREPEND 130 
#define  MSG_REQ_MC_REPLACE 129 
#define  MSG_REQ_MC_SET 128 

__attribute__((used)) static bool
memcache_storage(struct msg *r)
{
    switch (r->type) {
    case MSG_REQ_MC_SET:
    case MSG_REQ_MC_CAS:
    case MSG_REQ_MC_ADD:
    case MSG_REQ_MC_REPLACE:
    case MSG_REQ_MC_APPEND:
    case MSG_REQ_MC_PREPEND:
        return true;

    default:
        break;
    }

    return false;
}