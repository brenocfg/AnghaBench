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
typedef  scalar_t__ UErrorCode ;
typedef  char UChar ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 scalar_t__ U_BUFFER_OVERFLOW_ERROR ; 
 scalar_t__ U_SUCCESS (scalar_t__) ; 
 scalar_t__ U_ZERO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  icuFunctionError (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_realloc (char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text16 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 char* sqlite3_value_text16 (int /*<<< orphan*/ *) ; 
 int u_strToLower (char*,int,char const*,int,char const*,scalar_t__*) ; 
 int u_strToUpper (char*,int,char const*,int,char const*,scalar_t__*) ; 
 int /*<<< orphan*/  xFree ; 

__attribute__((used)) static void icuCaseFunc16(sqlite3_context *p, int nArg, sqlite3_value **apArg){
  const UChar *zInput;            /* Pointer to input string */
  UChar *zOutput = 0;             /* Pointer to output buffer */
  int nInput;                     /* Size of utf-16 input string in bytes */
  int nOut;                       /* Size of output buffer in bytes */
  int cnt;
  int bToUpper;                   /* True for toupper(), false for tolower() */
  UErrorCode status;
  const char *zLocale = 0;

  assert(nArg==1 || nArg==2);
  bToUpper = (sqlite3_user_data(p)!=0);
  if( nArg==2 ){
    zLocale = (const char *)sqlite3_value_text(apArg[1]);
  }

  zInput = sqlite3_value_text16(apArg[0]);
  if( !zInput ){
    return;
  }
  nOut = nInput = sqlite3_value_bytes16(apArg[0]);
  if( nOut==0 ){
    sqlite3_result_text16(p, "", 0, SQLITE_STATIC);
    return;
  }

  for(cnt=0; cnt<2; cnt++){
    UChar *zNew = sqlite3_realloc(zOutput, nOut);
    if( zNew==0 ){
      sqlite3_free(zOutput);
      sqlite3_result_error_nomem(p);
      return;
    }
    zOutput = zNew;
    status = U_ZERO_ERROR;
    if( bToUpper ){
      nOut = 2*u_strToUpper(zOutput,nOut/2,zInput,nInput/2,zLocale,&status);
    }else{
      nOut = 2*u_strToLower(zOutput,nOut/2,zInput,nInput/2,zLocale,&status);
    }

    if( U_SUCCESS(status) ){
      sqlite3_result_text16(p, zOutput, nOut, xFree);
    }else if( status==U_BUFFER_OVERFLOW_ERROR ){
      assert( cnt==0 );
      continue;
    }else{
      icuFunctionError(p, bToUpper ? "u_strToUpper" : "u_strToLower", status);
    }
    return;
  }
  assert( 0 );     /* Unreachable */
}