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
typedef  int u64 ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 

char *sqlite3DbStrNDup(sqlite3 *db, const char *z, u64 n){
  char *zNew;
  assert( db!=0 );
  if( z==0 ){
    return 0;
  }
  assert( (n&0x7fffffff)==n );
  zNew = sqlite3DbMallocRawNN(db, n+1);
  if( zNew ){
    memcpy(zNew, z, (size_t)n);
    zNew[n] = 0;
  }
  return zNew;
}