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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 void* sqlite3DbRealloc (int /*<<< orphan*/ *,void*,int) ; 

void *sqlite3ArrayAllocate(
  sqlite3 *db,      /* Connection to notify of malloc failures */
  void *pArray,     /* Array of objects.  Might be reallocated */
  int szEntry,      /* Size of each object in the array */
  int *pnEntry,     /* Number of objects currently in use */
  int *pIdx         /* Write the index of a new slot here */
){
  char *z;
  sqlite3_int64 n = *pIdx = *pnEntry;
  if( (n & (n-1))==0 ){
    sqlite3_int64 sz = (n==0) ? 1 : 2*n;
    void *pNew = sqlite3DbRealloc(db, pArray, sz*szEntry);
    if( pNew==0 ){
      *pIdx = -1;
      return pArray;
    }
    pArray = pNew;
  }
  z = (char*)pArray;
  memset(&z[n * szEntry], 0, szEntry);
  ++*pnEntry;
  return pArray;
}