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
typedef  int /*<<< orphan*/  ReCompiled ;

/* Variables and functions */
 char* re_compile (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  re_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_match (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/ * sqlite3_get_auxdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_set_auxdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*)) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void re_sql_func(
  sqlite3_context *context, 
  int argc, 
  sqlite3_value **argv
){
  ReCompiled *pRe;          /* Compiled regular expression */
  const char *zPattern;     /* The regular expression */
  const unsigned char *zStr;/* String being searched */
  const char *zErr;         /* Compile error message */
  int setAux = 0;           /* True to invoke sqlite3_set_auxdata() */

  pRe = sqlite3_get_auxdata(context, 0);
  if( pRe==0 ){
    zPattern = (const char*)sqlite3_value_text(argv[0]);
    if( zPattern==0 ) return;
    zErr = re_compile(&pRe, zPattern, 0);
    if( zErr ){
      re_free(pRe);
      sqlite3_result_error(context, zErr, -1);
      return;
    }
    if( pRe==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }
    setAux = 1;
  }
  zStr = (const unsigned char*)sqlite3_value_text(argv[1]);
  if( zStr!=0 ){
    sqlite3_result_int(context, re_match(pRe, zStr, -1));
  }
  if( setAux ){
    sqlite3_set_auxdata(context, 0, pRe, (void(*)(void*))re_free);
  }
}