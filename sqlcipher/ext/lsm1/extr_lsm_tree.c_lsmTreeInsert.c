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
 int LSM_INSERT ; 
 int LSM_POINT_DELETE ; 
 int treeInsertEntry (int /*<<< orphan*/ *,int,void*,int,void*,int) ; 

int lsmTreeInsert(
  lsm_db *pDb,                    /* Database handle */
  void *pKey,                     /* Pointer to key data */
  int nKey,                       /* Size of key data in bytes */
  void *pVal,                     /* Pointer to value data (or NULL) */
  int nVal                        /* Bytes in value data (or -ve for delete) */
){
  int flags;
  if( nVal<0 ){
    flags = LSM_POINT_DELETE;
  }else{
    flags = LSM_INSERT;
  }

  return treeInsertEntry(pDb, flags, pKey, nKey, pVal, nVal);
}