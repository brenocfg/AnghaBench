#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_str ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {int nVertex; } ;
typedef  TYPE_1__ GeoPoly ;

/* Variables and functions */
 int /*<<< orphan*/  GeoX (TYPE_1__*,int) ; 
 int /*<<< orphan*/  GeoY (TYPE_1__*,int) ; 
 TYPE_1__* geopolyFuncParam (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int /*<<< orphan*/  sqlite3_str_append (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_str_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_str_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void geopolyJsonFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  GeoPoly *p = geopolyFuncParam(context, argv[0], 0);
  if( p ){
    sqlite3 *db = sqlite3_context_db_handle(context);
    sqlite3_str *x = sqlite3_str_new(db);
    int i;
    sqlite3_str_append(x, "[", 1);
    for(i=0; i<p->nVertex; i++){
      sqlite3_str_appendf(x, "[%!g,%!g],", GeoX(p,i), GeoY(p,i));
    }
    sqlite3_str_appendf(x, "[%!g,%!g]]", GeoX(p,0), GeoY(p,0));
    sqlite3_result_text(context, sqlite3_str_finish(x), -1, sqlite3_free);
    sqlite3_free(p);
  }
}