#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  delivery_count; int /*<<< orphan*/  delivery_time; } ;
typedef  TYPE_1__ streamNACK ;
typedef  int /*<<< orphan*/  streamID ;
struct TYPE_6__ {char* name; } ;
typedef  TYPE_2__ streamConsumer ;
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  rio ;

/* Variables and functions */
 scalar_t__ rioWriteBulkCount (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ rioWriteBulkLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rioWriteBulkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rioWriteBulkStreamID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rioWriteBulkString (int /*<<< orphan*/ *,char const*,int) ; 
 int sdslen (char*) ; 
 int /*<<< orphan*/  streamDecodeID (unsigned char*,int /*<<< orphan*/ *) ; 

int rioWriteStreamPendingEntry(rio *r, robj *key, const char *groupname, size_t groupname_len, streamConsumer *consumer, unsigned char *rawid, streamNACK *nack) {
     /* XCLAIM <key> <group> <consumer> 0 <id> TIME <milliseconds-unix-time>
               RETRYCOUNT <count> JUSTID FORCE. */
    streamID id;
    streamDecodeID(rawid,&id);
    if (rioWriteBulkCount(r,'*',12) == 0) return 0;
    if (rioWriteBulkString(r,"XCLAIM",6) == 0) return 0;
    if (rioWriteBulkObject(r,key) == 0) return 0;
    if (rioWriteBulkString(r,groupname,groupname_len) == 0) return 0;
    if (rioWriteBulkString(r,consumer->name,sdslen(consumer->name)) == 0) return 0;
    if (rioWriteBulkString(r,"0",1) == 0) return 0;
    if (rioWriteBulkStreamID(r,&id) == 0) return 0;
    if (rioWriteBulkString(r,"TIME",4) == 0) return 0;
    if (rioWriteBulkLongLong(r,nack->delivery_time) == 0) return 0;
    if (rioWriteBulkString(r,"RETRYCOUNT",10) == 0) return 0;
    if (rioWriteBulkLongLong(r,nack->delivery_count) == 0) return 0;
    if (rioWriteBulkString(r,"JUSTID",6) == 0) return 0;
    if (rioWriteBulkString(r,"FORCE",5) == 0) return 0;
    return 1;
}