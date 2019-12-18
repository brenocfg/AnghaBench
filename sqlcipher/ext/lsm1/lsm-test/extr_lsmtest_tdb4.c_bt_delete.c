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
 int bt_write (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bt_delete(TestDb *pTestDb, void *pK, int nK){
  return bt_write(pTestDb, pK, nK, 0, -1);
}