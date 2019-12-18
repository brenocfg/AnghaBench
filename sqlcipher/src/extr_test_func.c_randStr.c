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
typedef  int /*<<< orphan*/  zSrc ;
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,...) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void randStr(sqlite3_context *context, int argc, sqlite3_value **argv){
  static const unsigned char zSrc[] = 
     "abcdefghijklmnopqrstuvwxyz"
     "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
     "0123456789"
     ".-!,:*^+=_|?/<> ";
  int iMin, iMax, n, r, i;
  unsigned char zBuf[1000];

  /* It used to be possible to call randstr() with any number of arguments,
  ** but now it is registered with SQLite as requiring exactly 2.
  */
  assert(argc==2);

  iMin = sqlite3_value_int(argv[0]);
  if( iMin<0 ) iMin = 0;
  if( iMin>=sizeof(zBuf) ) iMin = sizeof(zBuf)-1;
  iMax = sqlite3_value_int(argv[1]);
  if( iMax<iMin ) iMax = iMin;
  if( iMax>=sizeof(zBuf) ) iMax = sizeof(zBuf)-1;
  n = iMin;
  if( iMax>iMin ){
    sqlite3_randomness(sizeof(r), &r);
    r &= 0x7fffffff;
    n += r%(iMax + 1 - iMin);
  }
  assert( n<sizeof(zBuf) );
  sqlite3_randomness(n, zBuf);
  for(i=0; i<n; i++){
    zBuf[i] = zSrc[zBuf[i]%(sizeof(zSrc)-1)];
  }
  zBuf[n] = 0;
  sqlite3_result_text(context, (char*)zBuf, n, SQLITE_TRANSIENT);
}