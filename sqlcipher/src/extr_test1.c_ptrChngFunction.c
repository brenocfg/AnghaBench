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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_bytes16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text16 (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void ptrChngFunction(
  sqlite3_context *context, 
  int argc,  
  sqlite3_value **argv
){
  const void *p1, *p2;
  const char *zCmd;
  if( argc!=4 ) return;
  zCmd = (const char*)sqlite3_value_text(argv[1]);
  if( zCmd==0 ) return;
  if( strcmp(zCmd,"text")==0 ){
    p1 = (const void*)sqlite3_value_text(argv[0]);
#ifndef SQLITE_OMIT_UTF16
  }else if( strcmp(zCmd, "text16")==0 ){
    p1 = (const void*)sqlite3_value_text16(argv[0]);
#endif
  }else if( strcmp(zCmd, "blob")==0 ){
    p1 = (const void*)sqlite3_value_blob(argv[0]);
  }else{
    return;
  }
  zCmd = (const char*)sqlite3_value_text(argv[2]);
  if( zCmd==0 ) return;
  if( strcmp(zCmd,"bytes")==0 ){
    sqlite3_value_bytes(argv[0]);
#ifndef SQLITE_OMIT_UTF16
  }else if( strcmp(zCmd, "bytes16")==0 ){
    sqlite3_value_bytes16(argv[0]);
#endif
  }else if( strcmp(zCmd, "noop")==0 ){
    /* do nothing */
  }else{
    return;
  }
  zCmd = (const char*)sqlite3_value_text(argv[3]);
  if( zCmd==0 ) return;
  if( strcmp(zCmd,"text")==0 ){
    p2 = (const void*)sqlite3_value_text(argv[0]);
#ifndef SQLITE_OMIT_UTF16
  }else if( strcmp(zCmd, "text16")==0 ){
    p2 = (const void*)sqlite3_value_text16(argv[0]);
#endif
  }else if( strcmp(zCmd, "blob")==0 ){
    p2 = (const void*)sqlite3_value_blob(argv[0]);
  }else{
    return;
  }
  sqlite3_result_int(context, p1!=p2);
}