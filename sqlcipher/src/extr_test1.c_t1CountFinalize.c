#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; } ;
typedef  TYPE_1__ t1CountCtx ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 TYPE_1__* sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void t1CountFinalize(sqlite3_context *context){
  t1CountCtx *p;
  p = sqlite3_aggregate_context(context, sizeof(*p));
  if( p ){
    if( p->n==42 ){
      sqlite3_result_error(context, "x_count totals to 42", -1);
    }else{
      sqlite3_result_int(context, p ? p->n : 0);
    }
  }
}