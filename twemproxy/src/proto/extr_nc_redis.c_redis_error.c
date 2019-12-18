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
#define  MSG_RSP_REDIS_ERROR 141 
#define  MSG_RSP_REDIS_ERROR_BUSY 140 
#define  MSG_RSP_REDIS_ERROR_BUSYKEY 139 
#define  MSG_RSP_REDIS_ERROR_ERR 138 
#define  MSG_RSP_REDIS_ERROR_EXECABORT 137 
#define  MSG_RSP_REDIS_ERROR_LOADING 136 
#define  MSG_RSP_REDIS_ERROR_MASTERDOWN 135 
#define  MSG_RSP_REDIS_ERROR_MISCONF 134 
#define  MSG_RSP_REDIS_ERROR_NOAUTH 133 
#define  MSG_RSP_REDIS_ERROR_NOREPLICAS 132 
#define  MSG_RSP_REDIS_ERROR_NOSCRIPT 131 
#define  MSG_RSP_REDIS_ERROR_OOM 130 
#define  MSG_RSP_REDIS_ERROR_READONLY 129 
#define  MSG_RSP_REDIS_ERROR_WRONGTYPE 128 

__attribute__((used)) static bool
redis_error(struct msg *r)
{
    switch (r->type) {
    case MSG_RSP_REDIS_ERROR:
    case MSG_RSP_REDIS_ERROR_ERR:
    case MSG_RSP_REDIS_ERROR_OOM:
    case MSG_RSP_REDIS_ERROR_BUSY:
    case MSG_RSP_REDIS_ERROR_NOAUTH:
    case MSG_RSP_REDIS_ERROR_LOADING:
    case MSG_RSP_REDIS_ERROR_BUSYKEY:
    case MSG_RSP_REDIS_ERROR_MISCONF:
    case MSG_RSP_REDIS_ERROR_NOSCRIPT:
    case MSG_RSP_REDIS_ERROR_READONLY:
    case MSG_RSP_REDIS_ERROR_WRONGTYPE:
    case MSG_RSP_REDIS_ERROR_EXECABORT:
    case MSG_RSP_REDIS_ERROR_MASTERDOWN:
    case MSG_RSP_REDIS_ERROR_NOREPLICAS:
        return true;

    default:
        break;
    }

    return false;
}