#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct redisCommand {scalar_t__ proc; } ;
typedef  int /*<<< orphan*/  sds ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ robj ;

/* Variables and functions */
 int /*<<< orphan*/  catAppendOnlyGenericCommand (int /*<<< orphan*/ ,int,TYPE_1__**) ; 
 TYPE_1__* createStringObject (char*,int) ; 
 TYPE_1__* createStringObjectFromLongLong (long long) ; 
 int /*<<< orphan*/  decrRefCount (TYPE_1__*) ; 
 scalar_t__ expireCommand ; 
 scalar_t__ expireatCommand ; 
 TYPE_1__* getDecodedObject (TYPE_1__*) ; 
 scalar_t__ mstime () ; 
 scalar_t__ pexpireCommand ; 
 scalar_t__ psetexCommand ; 
 scalar_t__ setexCommand ; 
 long long strtoll (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

sds catAppendOnlyExpireAtCommand(sds buf, struct redisCommand *cmd, robj *key, robj *seconds) {
    long long when;
    robj *argv[3];

    /* Make sure we can use strtoll */
    seconds = getDecodedObject(seconds);
    when = strtoll(seconds->ptr,NULL,10);
    /* Convert argument into milliseconds for EXPIRE, SETEX, EXPIREAT */
    if (cmd->proc == expireCommand || cmd->proc == setexCommand ||
        cmd->proc == expireatCommand)
    {
        when *= 1000;
    }
    /* Convert into absolute time for EXPIRE, PEXPIRE, SETEX, PSETEX */
    if (cmd->proc == expireCommand || cmd->proc == pexpireCommand ||
        cmd->proc == setexCommand || cmd->proc == psetexCommand)
    {
        when += mstime();
    }
    decrRefCount(seconds);

    argv[0] = createStringObject("PEXPIREAT",9);
    argv[1] = key;
    argv[2] = createStringObjectFromLongLong(when);
    buf = catAppendOnlyGenericCommand(buf, 3, argv);
    decrRefCount(argv[0]);
    decrRefCount(argv[2]);
    return buf;
}