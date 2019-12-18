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
typedef  int /*<<< orphan*/  URegularExpression ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  int /*<<< orphan*/  UChar ;
typedef  scalar_t__ UBool ;

/* Variables and functions */
 scalar_t__ U_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  icuFunctionError (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icuRegexpDelete ; 
 int /*<<< orphan*/ * sqlite3_get_auxdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_set_auxdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_value_text16 (int /*<<< orphan*/ *) ; 
 scalar_t__ uregex_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uregex_open (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uregex_setText (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icuRegexpFunc(sqlite3_context *p, int nArg, sqlite3_value **apArg){
  UErrorCode status = U_ZERO_ERROR;
  URegularExpression *pExpr;
  UBool res;
  const UChar *zString = sqlite3_value_text16(apArg[1]);

  (void)nArg;  /* Unused parameter */

  /* If the left hand side of the regexp operator is NULL, 
  ** then the result is also NULL. 
  */
  if( !zString ){
    return;
  }

  pExpr = sqlite3_get_auxdata(p, 0);
  if( !pExpr ){
    const UChar *zPattern = sqlite3_value_text16(apArg[0]);
    if( !zPattern ){
      return;
    }
    pExpr = uregex_open(zPattern, -1, 0, 0, &status);

    if( U_SUCCESS(status) ){
      sqlite3_set_auxdata(p, 0, pExpr, icuRegexpDelete);
    }else{
      assert(!pExpr);
      icuFunctionError(p, "uregex_open", status);
      return;
    }
  }

  /* Configure the text that the regular expression operates on. */
  uregex_setText(pExpr, zString, -1, &status);
  if( !U_SUCCESS(status) ){
    icuFunctionError(p, "uregex_setText", status);
    return;
  }

  /* Attempt the match */
  res = uregex_matches(pExpr, 0, &status);
  if( !U_SUCCESS(status) ){
    icuFunctionError(p, "uregex_matches", status);
    return;
  }

  /* Set the text that the regular expression operates on to a NULL
  ** pointer. This is not really necessary, but it is tidier than 
  ** leaving the regular expression object configured with an invalid
  ** pointer after this function returns.
  */
  uregex_setText(pExpr, 0, 0, &status);

  /* Return 1 or 0. */
  sqlite3_result_int(p, res ? 1 : 0);
}