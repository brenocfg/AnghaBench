#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ robj ;
struct TYPE_10__ {int /*<<< orphan*/  zi; } ;
struct TYPE_12__ {TYPE_2__ entry; TYPE_1__* li; } ;
typedef  TYPE_4__ listTypeEntry ;
struct TYPE_9__ {scalar_t__ encoding; } ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int quicklistCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsEncodedObject (TYPE_3__*) ; 
 int /*<<< orphan*/  sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverAssertWithInfo (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int listTypeEqual(listTypeEntry *entry, robj *o) {
    if (entry->li->encoding == OBJ_ENCODING_QUICKLIST) {
        serverAssertWithInfo(NULL,o,sdsEncodedObject(o));
        return quicklistCompare(entry->entry.zi,o->ptr,sdslen(o->ptr));
    } else {
        serverPanic("Unknown list encoding");
    }
}