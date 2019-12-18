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
#define  MSG_REQ_REDIS_APPEND 148 
#define  MSG_REQ_REDIS_DECRBY 147 
#define  MSG_REQ_REDIS_EXPIRE 146 
#define  MSG_REQ_REDIS_EXPIREAT 145 
#define  MSG_REQ_REDIS_GETBIT 144 
#define  MSG_REQ_REDIS_GETSET 143 
#define  MSG_REQ_REDIS_HEXISTS 142 
#define  MSG_REQ_REDIS_HGET 141 
#define  MSG_REQ_REDIS_INCRBY 140 
#define  MSG_REQ_REDIS_INCRBYFLOAT 139 
#define  MSG_REQ_REDIS_LINDEX 138 
#define  MSG_REQ_REDIS_LPUSHX 137 
#define  MSG_REQ_REDIS_PEXPIRE 136 
#define  MSG_REQ_REDIS_PEXPIREAT 135 
#define  MSG_REQ_REDIS_RPOPLPUSH 134 
#define  MSG_REQ_REDIS_RPUSHX 133 
#define  MSG_REQ_REDIS_SETNX 132 
#define  MSG_REQ_REDIS_SISMEMBER 131 
#define  MSG_REQ_REDIS_ZRANK 130 
#define  MSG_REQ_REDIS_ZREVRANK 129 
#define  MSG_REQ_REDIS_ZSCORE 128 

__attribute__((used)) static bool
redis_arg1(struct msg *r)
{
    switch (r->type) {
    case MSG_REQ_REDIS_EXPIRE:
    case MSG_REQ_REDIS_EXPIREAT:
    case MSG_REQ_REDIS_PEXPIRE:
    case MSG_REQ_REDIS_PEXPIREAT:

    case MSG_REQ_REDIS_APPEND:
    case MSG_REQ_REDIS_DECRBY:
    case MSG_REQ_REDIS_GETBIT:
    case MSG_REQ_REDIS_GETSET:
    case MSG_REQ_REDIS_INCRBY:
    case MSG_REQ_REDIS_INCRBYFLOAT:
    case MSG_REQ_REDIS_SETNX:

    case MSG_REQ_REDIS_HEXISTS:
    case MSG_REQ_REDIS_HGET:

    case MSG_REQ_REDIS_LINDEX:
    case MSG_REQ_REDIS_LPUSHX:
    case MSG_REQ_REDIS_RPOPLPUSH:
    case MSG_REQ_REDIS_RPUSHX:

    case MSG_REQ_REDIS_SISMEMBER:

    case MSG_REQ_REDIS_ZRANK:
    case MSG_REQ_REDIS_ZREVRANK:
    case MSG_REQ_REDIS_ZSCORE:
        return true;

    default:
        break;
    }

    return false;
}