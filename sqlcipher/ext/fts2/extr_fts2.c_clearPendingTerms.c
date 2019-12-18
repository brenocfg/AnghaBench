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
struct TYPE_3__ {int nPendingData; int /*<<< orphan*/  pendingTerms; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  int /*<<< orphan*/  fts2HashElem ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  dlcDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts2HashClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts2HashData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts2HashFirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts2HashNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clearPendingTerms(fulltext_vtab *v){
  if( v->nPendingData>=0 ){
    fts2HashElem *e;
    for(e=fts2HashFirst(&v->pendingTerms); e; e=fts2HashNext(e)){
      dlcDelete(fts2HashData(e));
    }
    fts2HashClear(&v->pendingTerms);
    v->nPendingData = -1;
  }
  return SQLITE_OK;
}