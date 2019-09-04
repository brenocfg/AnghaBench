#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ encoding; int /*<<< orphan*/  iter; TYPE_1__* subject; } ;
typedef  TYPE_2__ listTypeIterator ;
struct TYPE_8__ {int /*<<< orphan*/  entry; TYPE_2__* li; } ;
typedef  TYPE_3__ listTypeEntry ;
struct TYPE_6__ {scalar_t__ encoding; } ;

/* Variables and functions */
 scalar_t__ OBJ_ENCODING_QUICKLIST ; 
 int quicklistNext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverPanic (char*) ; 

int listTypeNext(listTypeIterator *li, listTypeEntry *entry) {
    /* Protect from converting when iterating */
    serverAssert(li->subject->encoding == li->encoding);

    entry->li = li;
    if (li->encoding == OBJ_ENCODING_QUICKLIST) {
        return quicklistNext(li->iter, &entry->entry);
    } else {
        serverPanic("Unknown list encoding");
    }
    return 0;
}