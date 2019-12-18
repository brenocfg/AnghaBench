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
typedef  int /*<<< orphan*/  GeoPoly ;

/* Variables and functions */
 int /*<<< orphan*/ * geopolyFuncParam (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int geopolyOverlap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void geopolyWithinFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  GeoPoly *p1 = geopolyFuncParam(context, argv[0], 0);
  GeoPoly *p2 = geopolyFuncParam(context, argv[1], 0);
  if( p1 && p2 ){
    int x = geopolyOverlap(p1, p2);
    if( x<0 ){
      sqlite3_result_error_nomem(context);
    }else{
      sqlite3_result_int(context, x==2 ? 1 : x==4 ? 2 : 0);
    }
  }
  sqlite3_free(p1);
  sqlite3_free(p2);
}