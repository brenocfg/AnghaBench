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
typedef  int /*<<< orphan*/  TestDb ;

/* Variables and functions */
 int testLsmOpen (char const*,char const*,int,int /*<<< orphan*/ **) ; 

int tdb_lsm_open(const char *zCfg, const char *zDb, int bClear, TestDb **ppDb){
  return testLsmOpen(zCfg, zDb, bClear, ppDb);
}