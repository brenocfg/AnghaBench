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
 int /*<<< orphan*/  geopolyArea (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * geopolyFuncParam (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void geopolyAreaFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  GeoPoly *p = geopolyFuncParam(context, argv[0], 0);
  if( p ){
    sqlite3_result_double(context, geopolyArea(p));
    sqlite3_free(p);
  }            
}