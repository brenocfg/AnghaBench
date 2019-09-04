#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* zsl; } ;
typedef  TYPE_2__ zset ;
struct TYPE_9__ {scalar_t__ encoding; TYPE_2__* ptr; } ;
typedef  TYPE_3__ robj ;
struct TYPE_10__ {scalar_t__ zset_max_ziplist_entries; size_t zset_max_ziplist_value; } ;
struct TYPE_7__ {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_ZIPLIST ; 
 TYPE_6__ server ; 
 int /*<<< orphan*/  zsetConvert (TYPE_3__*,scalar_t__) ; 

void zsetConvertToZiplistIfNeeded(robj *zobj, size_t maxelelen) {
    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) return;
    zset *zset = zobj->ptr;

    if (zset->zsl->length <= server.zset_max_ziplist_entries &&
        maxelelen <= server.zset_max_ziplist_value)
            zsetConvert(zobj,OBJ_ENCODING_ZIPLIST);
}