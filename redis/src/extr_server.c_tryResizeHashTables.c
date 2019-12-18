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
struct TYPE_4__ {TYPE_1__* db; } ;
struct TYPE_3__ {int /*<<< orphan*/  expires; int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictResize (int /*<<< orphan*/ ) ; 
 scalar_t__ htNeedsResize (int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 

void tryResizeHashTables(int dbid) {
    if (htNeedsResize(server.db[dbid].dict))
        dictResize(server.db[dbid].dict);
    if (htNeedsResize(server.db[dbid].expires))
        dictResize(server.db[dbid].expires);
}