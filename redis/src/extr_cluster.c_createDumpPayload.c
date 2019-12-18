#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint64_t ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_8__ {void* ptr; } ;
struct TYPE_9__ {TYPE_1__ buffer; } ;
struct TYPE_10__ {TYPE_2__ io; } ;
typedef  TYPE_3__ rio ;

/* Variables and functions */
 int RDB_VERSION ; 
 unsigned char crc64 (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memrev64ifbe (unsigned char*) ; 
 int /*<<< orphan*/  rdbSaveObject (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdbSaveObjectType (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rioInitWithBuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 void* sdscatlen (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdslen (void*) ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 

void createDumpPayload(rio *payload, robj *o, robj *key) {
    unsigned char buf[2];
    uint64_t crc;

    /* Serialize the object in a RDB-like format. It consist of an object type
     * byte followed by the serialized object. This is understood by RESTORE. */
    rioInitWithBuffer(payload,sdsempty());
    serverAssert(rdbSaveObjectType(payload,o));
    serverAssert(rdbSaveObject(payload,o,key));

    /* Write the footer, this is how it looks like:
     * ----------------+---------------------+---------------+
     * ... RDB payload | 2 bytes RDB version | 8 bytes CRC64 |
     * ----------------+---------------------+---------------+
     * RDB version and CRC are both in little endian.
     */

    /* RDB version */
    buf[0] = RDB_VERSION & 0xff;
    buf[1] = (RDB_VERSION >> 8) & 0xff;
    payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,buf,2);

    /* CRC64 */
    crc = crc64(0,(unsigned char*)payload->io.buffer.ptr,
                sdslen(payload->io.buffer.ptr));
    memrev64ifbe(&crc);
    payload->io.buffer.ptr = sdscatlen(payload->io.buffer.ptr,&crc,8);
}