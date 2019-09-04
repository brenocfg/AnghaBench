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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  rio ;

/* Variables and functions */
 int /*<<< orphan*/  rdbExitReportCorruptRDB (char*,unsigned long long) ; 
 scalar_t__ rioRead (int /*<<< orphan*/ *,void*,scalar_t__) ; 

void rdbLoadRaw(rio *rdb, void *buf, uint64_t len) {
    if (rioRead(rdb,buf,len) == 0) {
        rdbExitReportCorruptRDB(
            "Impossible to read %llu bytes in rdbLoadRaw()",
            (unsigned long long) len);
        return; /* Not reached. */
    }
}