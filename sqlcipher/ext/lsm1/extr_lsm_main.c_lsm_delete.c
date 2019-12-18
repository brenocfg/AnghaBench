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
typedef  int /*<<< orphan*/  lsm_db ;

/* Variables and functions */
 int doWriteOp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ,int) ; 

int lsm_delete(lsm_db *db, const void *pKey, int nKey){
  return doWriteOp(db, 0, pKey, nKey, 0, -1);
}