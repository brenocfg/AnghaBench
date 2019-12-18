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
typedef  int /*<<< orphan*/  JsonString ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_SUBTYPE ; 
 int /*<<< orphan*/  jsonAppendChar (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  jsonAppendSeparator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonAppendValue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsonResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_subtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonArrayFunc(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  int i;
  JsonString jx;

  jsonInit(&jx, ctx);
  jsonAppendChar(&jx, '[');
  for(i=0; i<argc; i++){
    jsonAppendSeparator(&jx);
    jsonAppendValue(&jx, argv[i]);
  }
  jsonAppendChar(&jx, ']');
  jsonResult(&jx);
  sqlite3_result_subtype(ctx, JSON_SUBTYPE);
}