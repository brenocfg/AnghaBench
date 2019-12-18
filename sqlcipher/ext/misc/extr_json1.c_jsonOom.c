#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bErr; int /*<<< orphan*/  pCtx; } ;
typedef  TYPE_1__ JsonString ;

/* Variables and functions */
 int /*<<< orphan*/  jsonReset (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonOom(JsonString *p){
  p->bErr = 1;
  sqlite3_result_error_nomem(p->pCtx);
  jsonReset(p);
}