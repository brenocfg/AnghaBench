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
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
 int SQLITE_NULL ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  TOTYPE_BIGENDIAN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,unsigned char const*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned char* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  totypeAtoi64 (char const*,scalar_t__*,int) ; 
 int /*<<< orphan*/  totypeIsspace (unsigned char const) ; 

__attribute__((used)) static void tointegerFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  assert( argc==1 );
  (void)argc;
  switch( sqlite3_value_type(argv[0]) ){
    case SQLITE_FLOAT: {
      double rVal = sqlite3_value_double(argv[0]);
      sqlite3_int64 iVal = (sqlite3_int64)rVal;
      if( rVal==(double)iVal ){
        sqlite3_result_int64(context, iVal);
      }
      break;
    }
    case SQLITE_INTEGER: {
      sqlite3_result_int64(context, sqlite3_value_int64(argv[0]));
      break;
    }
    case SQLITE_BLOB: {
      const unsigned char *zBlob = sqlite3_value_blob(argv[0]);
      if( zBlob ){
        int nBlob = sqlite3_value_bytes(argv[0]);
        if( nBlob==sizeof(sqlite3_int64) ){
          sqlite3_int64 iVal;
          if( TOTYPE_BIGENDIAN ){
            int i;
            unsigned char zBlobRev[sizeof(sqlite3_int64)];
            for(i=0; i<sizeof(sqlite3_int64); i++){
              zBlobRev[i] = zBlob[sizeof(sqlite3_int64)-1-i];
            }
            memcpy(&iVal, zBlobRev, sizeof(sqlite3_int64));
          }else{
            memcpy(&iVal, zBlob, sizeof(sqlite3_int64));
          }
          sqlite3_result_int64(context, iVal);
        }
      }
      break;
    }
    case SQLITE_TEXT: {
      const unsigned char *zStr = sqlite3_value_text(argv[0]);
      if( zStr ){
        int nStr = sqlite3_value_bytes(argv[0]);
        if( nStr && !totypeIsspace(zStr[0]) ){
          sqlite3_int64 iVal;
          if( !totypeAtoi64((const char*)zStr, &iVal, nStr) ){
            sqlite3_result_int64(context, iVal);
          }
        }
      }
      break;
    }
    default: {
      assert( sqlite3_value_type(argv[0])==SQLITE_NULL );
      break;
    }
  }
}