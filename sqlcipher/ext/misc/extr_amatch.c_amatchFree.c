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
struct TYPE_7__ {struct TYPE_7__* zSelf; struct TYPE_7__* zVocabLang; struct TYPE_7__* zVocabWord; struct TYPE_7__* zVocabTab; struct TYPE_7__* zCostTab; struct TYPE_7__* zDb; struct TYPE_7__* zClassName; } ;
typedef  TYPE_1__ amatch_vtab ;

/* Variables and functions */
 int /*<<< orphan*/  amatchFreeRules (TYPE_1__*) ; 
 int /*<<< orphan*/  amatchVCheckClear (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static void amatchFree(amatch_vtab *p){
  if( p ){
    amatchFreeRules(p);
    amatchVCheckClear(p);
    sqlite3_free(p->zClassName);
    sqlite3_free(p->zDb);
    sqlite3_free(p->zCostTab);
    sqlite3_free(p->zVocabTab);
    sqlite3_free(p->zVocabWord);
    sqlite3_free(p->zVocabLang);
    sqlite3_free(p->zSelf);
    memset(p, 0, sizeof(*p));
    sqlite3_free(p);
  }
}