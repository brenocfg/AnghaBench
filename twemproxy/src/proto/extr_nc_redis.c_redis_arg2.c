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
#define  MSG_REQ_REDIS_GETRANGE 148 
#define  MSG_REQ_REDIS_HINCRBY 147 
#define  MSG_REQ_REDIS_HINCRBYFLOAT 146 
#define  MSG_REQ_REDIS_HSET 145 
#define  MSG_REQ_REDIS_HSETNX 144 
#define  MSG_REQ_REDIS_LRANGE 143 
#define  MSG_REQ_REDIS_LREM 142 
#define  MSG_REQ_REDIS_LSET 141 
#define  MSG_REQ_REDIS_LTRIM 140 
#define  MSG_REQ_REDIS_PSETEX 139 
#define  MSG_REQ_REDIS_RESTORE 138 
#define  MSG_REQ_REDIS_SETBIT 137 
#define  MSG_REQ_REDIS_SETEX 136 
#define  MSG_REQ_REDIS_SETRANGE 135 
#define  MSG_REQ_REDIS_SMOVE 134 
#define  MSG_REQ_REDIS_ZCOUNT 133 
#define  MSG_REQ_REDIS_ZINCRBY 132 
#define  MSG_REQ_REDIS_ZLEXCOUNT 131 
#define  MSG_REQ_REDIS_ZREMRANGEBYLEX 130 
#define  MSG_REQ_REDIS_ZREMRANGEBYRANK 129 
#define  MSG_REQ_REDIS_ZREMRANGEBYSCORE 128 

__attribute__((used)) static bool
redis_arg2(struct msg *r)
{
    switch (r->type) {
    case MSG_REQ_REDIS_GETRANGE:
    case MSG_REQ_REDIS_PSETEX:
    case MSG_REQ_REDIS_SETBIT:
    case MSG_REQ_REDIS_SETEX:
    case MSG_REQ_REDIS_SETRANGE:

    case MSG_REQ_REDIS_HINCRBY:
    case MSG_REQ_REDIS_HINCRBYFLOAT:
    case MSG_REQ_REDIS_HSET:
    case MSG_REQ_REDIS_HSETNX:

    case MSG_REQ_REDIS_LRANGE:
    case MSG_REQ_REDIS_LREM:
    case MSG_REQ_REDIS_LSET:
    case MSG_REQ_REDIS_LTRIM:

    case MSG_REQ_REDIS_SMOVE:

    case MSG_REQ_REDIS_ZCOUNT:
    case MSG_REQ_REDIS_ZLEXCOUNT:
    case MSG_REQ_REDIS_ZINCRBY:
    case MSG_REQ_REDIS_ZREMRANGEBYLEX:
    case MSG_REQ_REDIS_ZREMRANGEBYRANK:
    case MSG_REQ_REDIS_ZREMRANGEBYSCORE:

    case MSG_REQ_REDIS_RESTORE:
        return true;

    default:
        break;
    }

    return false;
}