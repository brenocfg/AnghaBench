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
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UCollator ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF16 ; 
 int /*<<< orphan*/  U_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  icuCollationColl ; 
 int /*<<< orphan*/  icuCollationDel ; 
 int /*<<< orphan*/  icuFunctionError (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sqlite3_create_collation_v2 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucol_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ucol_open (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icuLoadCollation(
  sqlite3_context *p, 
  int nArg, 
  sqlite3_value **apArg
){
  sqlite3 *db = (sqlite3 *)sqlite3_user_data(p);
  UErrorCode status = U_ZERO_ERROR;
  const char *zLocale;      /* Locale identifier - (eg. "jp_JP") */
  const char *zName;        /* SQL Collation sequence name (eg. "japanese") */
  UCollator *pUCollator;    /* ICU library collation object */
  int rc;                   /* Return code from sqlite3_create_collation_x() */

  assert(nArg==2);
  (void)nArg; /* Unused parameter */
  zLocale = (const char *)sqlite3_value_text(apArg[0]);
  zName = (const char *)sqlite3_value_text(apArg[1]);

  if( !zLocale || !zName ){
    return;
  }

  pUCollator = ucol_open(zLocale, &status);
  if( !U_SUCCESS(status) ){
    icuFunctionError(p, "ucol_open", status);
    return;
  }
  assert(p);

  rc = sqlite3_create_collation_v2(db, zName, SQLITE_UTF16, (void *)pUCollator, 
      icuCollationColl, icuCollationDel
  );
  if( rc!=SQLITE_OK ){
    ucol_close(pUCollator);
    sqlite3_result_error(p, "Error registering collation function", -1);
  }
}