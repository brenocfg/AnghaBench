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
#define  MSG_REQ_REDIS_AUTH 149 
#define  MSG_REQ_REDIS_DECR 148 
#define  MSG_REQ_REDIS_DUMP 147 
#define  MSG_REQ_REDIS_EXISTS 146 
#define  MSG_REQ_REDIS_GET 145 
#define  MSG_REQ_REDIS_HGETALL 144 
#define  MSG_REQ_REDIS_HKEYS 143 
#define  MSG_REQ_REDIS_HLEN 142 
#define  MSG_REQ_REDIS_HVALS 141 
#define  MSG_REQ_REDIS_INCR 140 
#define  MSG_REQ_REDIS_LLEN 139 
#define  MSG_REQ_REDIS_LPOP 138 
#define  MSG_REQ_REDIS_PERSIST 137 
#define  MSG_REQ_REDIS_PFCOUNT 136 
#define  MSG_REQ_REDIS_PTTL 135 
#define  MSG_REQ_REDIS_RPOP 134 
#define  MSG_REQ_REDIS_SCARD 133 
#define  MSG_REQ_REDIS_SMEMBERS 132 
#define  MSG_REQ_REDIS_STRLEN 131 
#define  MSG_REQ_REDIS_TTL 130 
#define  MSG_REQ_REDIS_TYPE 129 
#define  MSG_REQ_REDIS_ZCARD 128 

__attribute__((used)) static bool
redis_arg0(struct msg *r)
{
    switch (r->type) {
    case MSG_REQ_REDIS_EXISTS:
    case MSG_REQ_REDIS_PERSIST:
    case MSG_REQ_REDIS_PTTL:
    case MSG_REQ_REDIS_TTL:
    case MSG_REQ_REDIS_TYPE:
    case MSG_REQ_REDIS_DUMP:

    case MSG_REQ_REDIS_DECR:
    case MSG_REQ_REDIS_GET:
    case MSG_REQ_REDIS_INCR:
    case MSG_REQ_REDIS_STRLEN:

    case MSG_REQ_REDIS_HGETALL:
    case MSG_REQ_REDIS_HKEYS:
    case MSG_REQ_REDIS_HLEN:
    case MSG_REQ_REDIS_HVALS:

    case MSG_REQ_REDIS_LLEN:
    case MSG_REQ_REDIS_LPOP:
    case MSG_REQ_REDIS_RPOP:

    case MSG_REQ_REDIS_SCARD:
    case MSG_REQ_REDIS_SMEMBERS:

    case MSG_REQ_REDIS_ZCARD:
    case MSG_REQ_REDIS_PFCOUNT:
    case MSG_REQ_REDIS_AUTH:
        return true;

    default:
        break;
    }

    return false;
}