#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* pTerm; } ;
struct TYPE_5__ {int nTerms; TYPE_2__* pTerms; } ;
typedef  TYPE_1__ Query ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 

__attribute__((used)) static void queryClear(Query *q){
  int i;
  for(i = 0; i < q->nTerms; ++i){
    sqlite3_free(q->pTerms[i].pTerm);
  }
  sqlite3_free(q->pTerms);
  CLEAR(q);
}