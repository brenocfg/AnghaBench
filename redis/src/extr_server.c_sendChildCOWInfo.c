#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t cow_size; } ;
struct TYPE_4__ {TYPE_1__ child_info_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  sendChildInfo (int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,char*,size_t) ; 
 size_t zmalloc_get_private_dirty (int) ; 

void sendChildCOWInfo(int ptype, char *pname) {
    size_t private_dirty = zmalloc_get_private_dirty(-1);

    if (private_dirty) {
        serverLog(LL_NOTICE,
            "%s: %zu MB of memory used by copy-on-write",
            pname, private_dirty/(1024*1024));
    }

    server.child_info_data.cow_size = private_dirty;
    sendChildInfo(ptype);
}