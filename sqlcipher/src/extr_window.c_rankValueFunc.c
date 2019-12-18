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
struct CallCount {scalar_t__ nValue; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void rankValueFunc(sqlite3_context *pCtx){
  struct CallCount *p;
  p = (struct CallCount*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p ){
    sqlite3_result_int64(pCtx, p->nValue);
    p->nValue = 0;
  }
}