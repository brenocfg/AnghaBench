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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  memrev64ifbe (scalar_t__*) ; 
 int /*<<< orphan*/  rdbLoadRaw (int /*<<< orphan*/ *,scalar_t__*,int) ; 

long long rdbLoadMillisecondTime(rio *rdb, int rdbver) {
    int64_t t64;
    rdbLoadRaw(rdb,&t64,8);
    if (rdbver >= 9) /* Check the top comment of this function. */
        memrev64ifbe(&t64); /* Convert in big endian if the system is BE. */
    return (long long)t64;
}