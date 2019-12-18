#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  aAll; } ;
struct TYPE_7__ {int nToken; TYPE_1__* aToken; TYPE_4__ doclist; } ;
struct TYPE_6__ {scalar_t__ pSegcsr; } ;
typedef  TYPE_2__ Fts3Phrase ;
typedef  int /*<<< orphan*/  Fts3Doclist ;

/* Variables and functions */
 int /*<<< orphan*/  fts3EvalInvalidatePoslist (TYPE_2__*) ; 
 int /*<<< orphan*/  fts3SegReaderCursorFree (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

void sqlite3Fts3EvalPhraseCleanup(Fts3Phrase *pPhrase){
  if( pPhrase ){
    int i;
    sqlite3_free(pPhrase->doclist.aAll);
    fts3EvalInvalidatePoslist(pPhrase);
    memset(&pPhrase->doclist, 0, sizeof(Fts3Doclist));
    for(i=0; i<pPhrase->nToken; i++){
      fts3SegReaderCursorFree(pPhrase->aToken[i].pSegcsr);
      pPhrase->aToken[i].pSegcsr = 0;
    }
  }
}