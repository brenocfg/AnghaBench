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
struct groupConcat {size_t nUsed; scalar_t__* z; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 struct groupConcat* sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,scalar_t__*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void groupFinal(sqlite3_context *context){
  struct groupConcat *p;
  p = sqlite3_aggregate_context(context, 0);
  if( p && p->z ){
    p->z[p->nUsed] = 0;
    sqlite3_result_text(context, p->z, p->nUsed, sqlite3_free);
  }
}