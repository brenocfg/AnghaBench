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
typedef  int /*<<< orphan*/  sqliterk ;

/* Variables and functions */
 int sqliterkParsePage (int /*<<< orphan*/ *,int) ; 

int sqliterkParseMaster(sqliterk *rk)
{
    // The page 1 is always sqlite_master. See [B-tree Pages] at
    // https://www.sqlite.org/fileformat2.html
    return sqliterkParsePage(rk, 1);
}