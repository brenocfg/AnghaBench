#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* xCmp ) (void*,int,void*,int) ;} ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_OK ; 
 int doWriteOp (TYPE_1__*,int,void const*,int,void const*,int) ; 
 scalar_t__ stub1 (void*,int,void*,int) ; 

int lsm_delete_range(
  lsm_db *db,                     /* Database handle */
  const void *pKey1, int nKey1,   /* Lower bound of range to delete */
  const void *pKey2, int nKey2    /* Upper bound of range to delete */
){
  int rc = LSM_OK;
  if( db->xCmp((void *)pKey1, nKey1, (void *)pKey2, nKey2)<0 ){
    rc = doWriteOp(db, 1, pKey1, nKey1, pKey2, nKey2);
  }
  return rc;
}