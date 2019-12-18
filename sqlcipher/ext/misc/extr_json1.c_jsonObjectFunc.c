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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  JsonString ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_SUBTYPE ; 
 scalar_t__ SQLITE_TEXT ; 
 int /*<<< orphan*/  jsonAppendChar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  jsonAppendSeparator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonAppendString (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  jsonAppendValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_subtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jsonObjectFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  int i;
  JsonString jx;
  const char *z;
  u32 n;

  if( argc&1 ){
    sqlite3_result_error(ctx, "json_object() requires an even number "
                                  "of arguments", -1);
    return;
  }
  jsonInit(&jx, ctx);
  jsonAppendChar(&jx, '{');
  for(i=0; i<argc; i+=2){
    if( sqlite3_value_type(argv[i])!=SQLITE_TEXT ){
      sqlite3_result_error(ctx, "json_object() labels must be TEXT", -1);
      jsonReset(&jx);
      return;
    }
    jsonAppendSeparator(&jx);
    z = (const char*)sqlite3_value_text(argv[i]);
    n = (u32)sqlite3_value_bytes(argv[i]);
    jsonAppendString(&jx, z, n);
    jsonAppendChar(&jx, ':');
    jsonAppendValue(&jx, argv[i+1]);
  }
  jsonAppendChar(&jx, '}');
  jsonResult(&jx);
  sqlite3_result_subtype(ctx, JSON_SUBTYPE);
}