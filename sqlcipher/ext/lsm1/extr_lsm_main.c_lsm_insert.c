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
 int doWriteOp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int,void const*,int) ; 

int lsm_insert(
  lsm_db *db,                     /* Database connection */
  const void *pKey, int nKey,     /* Key to write or delete */
  const void *pVal, int nVal      /* Value to write. Or nVal==-1 for a delete */
){
  return doWriteOp(db, 0, pKey, nKey, pVal, nVal);
}