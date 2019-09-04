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
typedef  int /*<<< orphan*/  rio ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memrev64ifbe (int /*<<< orphan*/ *) ; 
 int rdbWriteRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int rdbSaveMillisecondTime(rio *rdb, long long t) {
    int64_t t64 = (int64_t) t;
    memrev64ifbe(&t64); /* Store in little endian. */
    return rdbWriteRaw(rdb,&t64,8);
}