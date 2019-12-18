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
struct TYPE_3__ {int nParam; int /*<<< orphan*/ * apSqlParam; } ;
typedef  TYPE_1__ RtreeMatchArg ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_value_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtreeMatchArgFree(void *pArg){
  int i;
  RtreeMatchArg *p = (RtreeMatchArg*)pArg;
  for(i=0; i<p->nParam; i++){
    sqlite3_value_free(p->apSqlParam[i]);
  }
  sqlite3_free(p);
}