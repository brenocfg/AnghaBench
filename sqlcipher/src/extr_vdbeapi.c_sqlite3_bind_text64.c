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
typedef  int sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 void SQLITE_DYNAMIC (void*) ; 
 unsigned char SQLITE_UTF16 ; 
 unsigned char SQLITE_UTF16NATIVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int bindText (int /*<<< orphan*/ *,int,char const*,int,void (*) (void*),unsigned char) ; 
 int invokeValueDestructor (char const*,void (*) (void*),int /*<<< orphan*/ ) ; 

int sqlite3_bind_text64( 
  sqlite3_stmt *pStmt, 
  int i, 
  const char *zData, 
  sqlite3_uint64 nData, 
  void (*xDel)(void*),
  unsigned char enc
){
  assert( xDel!=SQLITE_DYNAMIC );
  if( nData>0x7fffffff ){
    return invokeValueDestructor(zData, xDel, 0);
  }else{
    if( enc==SQLITE_UTF16 ) enc = SQLITE_UTF16NATIVE;
    return bindText(pStmt, i, zData, (int)nData, xDel, enc);
  }
}