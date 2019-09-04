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
#define  MSG_REQ_REDIS_BITCOUNT 160 
#define  MSG_REQ_REDIS_BITPOS 159 
#define  MSG_REQ_REDIS_HDEL 158 
#define  MSG_REQ_REDIS_HMGET 157 
#define  MSG_REQ_REDIS_HMSET 156 
#define  MSG_REQ_REDIS_HSCAN 155 
#define  MSG_REQ_REDIS_LPUSH 154 
#define  MSG_REQ_REDIS_PFADD 153 
#define  MSG_REQ_REDIS_PFMERGE 152 
#define  MSG_REQ_REDIS_RPUSH 151 
#define  MSG_REQ_REDIS_SADD 150 
#define  MSG_REQ_REDIS_SDIFF 149 
#define  MSG_REQ_REDIS_SDIFFSTORE 148 
#define  MSG_REQ_REDIS_SET 147 
#define  MSG_REQ_REDIS_SINTER 146 
#define  MSG_REQ_REDIS_SINTERSTORE 145 
#define  MSG_REQ_REDIS_SORT 144 
#define  MSG_REQ_REDIS_SPOP 143 
#define  MSG_REQ_REDIS_SRANDMEMBER 142 
#define  MSG_REQ_REDIS_SREM 141 
#define  MSG_REQ_REDIS_SSCAN 140 
#define  MSG_REQ_REDIS_SUNION 139 
#define  MSG_REQ_REDIS_SUNIONSTORE 138 
#define  MSG_REQ_REDIS_ZADD 137 
#define  MSG_REQ_REDIS_ZINTERSTORE 136 
#define  MSG_REQ_REDIS_ZRANGE 135 
#define  MSG_REQ_REDIS_ZRANGEBYLEX 134 
#define  MSG_REQ_REDIS_ZRANGEBYSCORE 133 
#define  MSG_REQ_REDIS_ZREM 132 
#define  MSG_REQ_REDIS_ZREVRANGE 131 
#define  MSG_REQ_REDIS_ZREVRANGEBYSCORE 130 
#define  MSG_REQ_REDIS_ZSCAN 129 
#define  MSG_REQ_REDIS_ZUNIONSTORE 128 

__attribute__((used)) static bool
redis_argn(struct msg *r)
{
    switch (r->type) {
    case MSG_REQ_REDIS_SORT:

    case MSG_REQ_REDIS_BITCOUNT:
    case MSG_REQ_REDIS_BITPOS:

    case MSG_REQ_REDIS_SET:
    case MSG_REQ_REDIS_HDEL:
    case MSG_REQ_REDIS_HMGET:
    case MSG_REQ_REDIS_HMSET:
    case MSG_REQ_REDIS_HSCAN:

    case MSG_REQ_REDIS_LPUSH:
    case MSG_REQ_REDIS_RPUSH:

    case MSG_REQ_REDIS_SADD:
    case MSG_REQ_REDIS_SDIFF:
    case MSG_REQ_REDIS_SDIFFSTORE:
    case MSG_REQ_REDIS_SINTER:
    case MSG_REQ_REDIS_SINTERSTORE:
    case MSG_REQ_REDIS_SREM:
    case MSG_REQ_REDIS_SUNION:
    case MSG_REQ_REDIS_SUNIONSTORE:
    case MSG_REQ_REDIS_SRANDMEMBER:
    case MSG_REQ_REDIS_SSCAN:
    case MSG_REQ_REDIS_SPOP:

    case MSG_REQ_REDIS_PFADD:
    case MSG_REQ_REDIS_PFMERGE:

    case MSG_REQ_REDIS_ZADD:
    case MSG_REQ_REDIS_ZINTERSTORE:
    case MSG_REQ_REDIS_ZRANGE:
    case MSG_REQ_REDIS_ZRANGEBYSCORE:
    case MSG_REQ_REDIS_ZREM:
    case MSG_REQ_REDIS_ZREVRANGE:
    case MSG_REQ_REDIS_ZRANGEBYLEX:
    case MSG_REQ_REDIS_ZREVRANGEBYSCORE:
    case MSG_REQ_REDIS_ZUNIONSTORE:
    case MSG_REQ_REDIS_ZSCAN:
        return true;

    default:
        break;
    }

    return false;
}