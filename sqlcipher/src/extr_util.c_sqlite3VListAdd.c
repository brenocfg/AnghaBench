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
typedef  int VList ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int* sqlite3DbRealloc (int /*<<< orphan*/ *,int*,int) ; 

VList *sqlite3VListAdd(
  sqlite3 *db,           /* The database connection used for malloc() */
  VList *pIn,            /* The input VList.  Might be NULL */
  const char *zName,     /* Name of symbol to add */
  int nName,             /* Bytes of text in zName */
  int iVal               /* Value to associate with zName */
){
  int nInt;              /* number of sizeof(int) objects needed for zName */
  char *z;               /* Pointer to where zName will be stored */
  int i;                 /* Index in pIn[] where zName is stored */

  nInt = nName/4 + 3;
  assert( pIn==0 || pIn[0]>=3 );  /* Verify ok to add new elements */
  if( pIn==0 || pIn[1]+nInt > pIn[0] ){
    /* Enlarge the allocation */
    sqlite3_int64 nAlloc = (pIn ? 2*(sqlite3_int64)pIn[0] : 10) + nInt;
    VList *pOut = sqlite3DbRealloc(db, pIn, nAlloc*sizeof(int));
    if( pOut==0 ) return pIn;
    if( pIn==0 ) pOut[1] = 2;
    pIn = pOut;
    pIn[0] = nAlloc;
  }
  i = pIn[1];
  pIn[i] = iVal;
  pIn[i+1] = nInt;
  z = (char*)&pIn[i+2];
  pIn[1] = i+nInt;
  assert( pIn[1]<=pIn[0] );
  memcpy(z, zName, nName);
  z[nName] = 0;
  return pIn;
}