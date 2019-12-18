#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_8__ {int iWrite; } ;
struct TYPE_9__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_10__ {int nKey; int nValue; scalar_t__ flags; } ;
typedef  TYPE_3__ TreeKey ;

/* Variables and functions */
 scalar_t__ LSM_CONTIGUOUS ; 
 int LSM_MAX (int,int) ; 
 int LSM_MIN (int,int) ; 
 int LSM_SHM_CHUNK_HDR ; 
 int LSM_SHM_CHUNK_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int treeShmalloc (TYPE_2__*,int,int,int*) ; 
 void* treeShmptr (TYPE_2__*,int) ; 

__attribute__((used)) static TreeKey *newTreeKey(
  lsm_db *pDb, 
  u32 *piPtr, 
  void *pKey, int nKey,           /* Key data */
  void *pVal, int nVal,           /* Value data (or nVal<0 for delete) */
  int *pRc
){
  TreeKey *p;
  u32 iPtr;
  u32 iEnd;
  int nRem;
  u8 *a;
  int n;

  /* Allocate space for the TreeKey structure itself */
  *piPtr = iPtr = treeShmalloc(pDb, 1, sizeof(TreeKey), pRc);
  p = treeShmptr(pDb, iPtr);
  if( *pRc ) return 0;
  p->nKey = nKey;
  p->nValue = nVal;

  /* Allocate and populate the space required for the key and value. */
  n = nRem = nKey;
  a = (u8 *)pKey;
  while( a ){
    while( nRem>0 ){
      u8 *aAlloc;
      int nAlloc;
      u32 iWrite;

      iWrite = (pDb->treehdr.iWrite & (LSM_SHM_CHUNK_SIZE-1));
      iWrite = LSM_MAX(iWrite, LSM_SHM_CHUNK_HDR);
      nAlloc = LSM_MIN((LSM_SHM_CHUNK_SIZE-iWrite), (u32)nRem);

      aAlloc = treeShmptr(pDb, treeShmalloc(pDb, 0, nAlloc, pRc));
      if( aAlloc==0 ) break;
      memcpy(aAlloc, &a[n-nRem], nAlloc);
      nRem -= nAlloc;
    }
    a = pVal;
    n = nRem = nVal;
    pVal = 0;
  }

  iEnd = iPtr + sizeof(TreeKey) + nKey + LSM_MAX(0, nVal);
  if( (iPtr & ~(LSM_SHM_CHUNK_SIZE-1))!=(iEnd & ~(LSM_SHM_CHUNK_SIZE-1)) ){
    p->flags = 0;
  }else{
    p->flags = LSM_CONTIGUOUS;
  }

  if( *pRc ) return 0;
#if 0
  printf("store: %d %s\n", (int)iPtr, (char *)pKey);
#endif
  return p;
}