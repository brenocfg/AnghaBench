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
typedef  double sqlite3_int64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  SQLITE_BLOB 132 
#define  SQLITE_FLOAT 131 
#define  SQLITE_INTEGER 130 
#define  SQLITE_NULL 129 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,double*,int) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putsVarint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_blob (int /*<<< orphan*/ *,int) ; 
 double sqlite3_column_bytes (int /*<<< orphan*/ *,int) ; 
 double sqlite3_column_double (int /*<<< orphan*/ *,int) ; 
 double sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_column_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void putValue(FILE *out, sqlite3_stmt *pStmt, int k){
  int iDType = sqlite3_column_type(pStmt, k);
  sqlite3_int64 iX;
  double rX;
  sqlite3_uint64 uX;
  int j;

  putc(iDType, out);
  switch( iDType ){
    case SQLITE_INTEGER:
      iX = sqlite3_column_int64(pStmt, k);
      memcpy(&uX, &iX, 8);
      for(j=56; j>=0; j-=8) putc((uX>>j)&0xff, out);
      break;
    case SQLITE_FLOAT:
      rX = sqlite3_column_double(pStmt, k);
      memcpy(&uX, &rX, 8);
      for(j=56; j>=0; j-=8) putc((uX>>j)&0xff, out);
      break;
    case SQLITE_TEXT:
      iX = sqlite3_column_bytes(pStmt, k);
      putsVarint(out, (sqlite3_uint64)iX);
      fwrite(sqlite3_column_text(pStmt, k),1,(size_t)iX,out);
      break;
    case SQLITE_BLOB:
      iX = sqlite3_column_bytes(pStmt, k);
      putsVarint(out, (sqlite3_uint64)iX);
      fwrite(sqlite3_column_blob(pStmt, k),1,(size_t)iX,out);
      break;
    case SQLITE_NULL:
      break;
  }
}