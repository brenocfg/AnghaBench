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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  rio ;
struct TYPE_2__ {int maxmemory_policy; scalar_t__ rdb_key_save_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  LFUDecrAndReturn (int /*<<< orphan*/ *) ; 
 int MAXMEMORY_FLAG_LFU ; 
 int MAXMEMORY_FLAG_LRU ; 
 int /*<<< orphan*/  RDB_OPCODE_EXPIRETIME_MS ; 
 int /*<<< orphan*/  RDB_OPCODE_FREQ ; 
 int /*<<< orphan*/  RDB_OPCODE_IDLE ; 
 int estimateObjectIdleTime (int /*<<< orphan*/ *) ; 
 int rdbSaveLen (int /*<<< orphan*/ *,int) ; 
 int rdbSaveMillisecondTime (int /*<<< orphan*/ *,long long) ; 
 int rdbSaveObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rdbSaveObjectType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rdbSaveStringObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int rdbSaveType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdbWriteRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val, long long expiretime) {
    int savelru = server.maxmemory_policy & MAXMEMORY_FLAG_LRU;
    int savelfu = server.maxmemory_policy & MAXMEMORY_FLAG_LFU;

    /* Save the expire time */
    if (expiretime != -1) {
        if (rdbSaveType(rdb,RDB_OPCODE_EXPIRETIME_MS) == -1) return -1;
        if (rdbSaveMillisecondTime(rdb,expiretime) == -1) return -1;
    }

    /* Save the LRU info. */
    if (savelru) {
        uint64_t idletime = estimateObjectIdleTime(val);
        idletime /= 1000; /* Using seconds is enough and requires less space.*/
        if (rdbSaveType(rdb,RDB_OPCODE_IDLE) == -1) return -1;
        if (rdbSaveLen(rdb,idletime) == -1) return -1;
    }

    /* Save the LFU info. */
    if (savelfu) {
        uint8_t buf[1];
        buf[0] = LFUDecrAndReturn(val);
        /* We can encode this in exactly two bytes: the opcode and an 8
         * bit counter, since the frequency is logarithmic with a 0-255 range.
         * Note that we do not store the halving time because to reset it
         * a single time when loading does not affect the frequency much. */
        if (rdbSaveType(rdb,RDB_OPCODE_FREQ) == -1) return -1;
        if (rdbWriteRaw(rdb,buf,1) == -1) return -1;
    }

    /* Save type, key, value */
    if (rdbSaveObjectType(rdb,val) == -1) return -1;
    if (rdbSaveStringObject(rdb,key) == -1) return -1;
    if (rdbSaveObject(rdb,val,key) == -1) return -1;

    /* Delay return if required (for testing) */
    if (server.rdb_key_save_delay)
        usleep(server.rdb_key_save_delay);

    return 1;
}