#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_7__ {scalar_t__ bPatchset; } ;
struct TYPE_6__ {char* zTab; int nCol; int nChange; scalar_t__* aChange; scalar_t__* aPK; } ;
typedef  TYPE_1__ FuzzChangesetGroup ;
typedef  TYPE_2__ FuzzChangeset ;

/* Variables and functions */
 scalar_t__ SQLITE_DELETE ; 
 scalar_t__ SQLITE_INSERT ; 
 scalar_t__ SQLITE_UPDATE ; 
 int /*<<< orphan*/  fuzzPrintRecord (TYPE_1__*,scalar_t__**,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void fuzzPrintGroup(FuzzChangeset *pParse, FuzzChangesetGroup *pGrp){
  int i;
  u8 *p;

  /* The table header */
  printf("TABLE:  %s nCol=%d aPK=", pGrp->zTab, pGrp->nCol);
  for(i=0; i<pGrp->nCol; i++){
    printf("%d", (int)pGrp->aPK[i]);
  }
  printf("\n");

  /* The array of changes */
  p = pGrp->aChange;
  for(i=0; i<pGrp->nChange; i++){
    u8 eType = p[0];
    u8 bIndirect = p[1];
    printf("%s (ind=%d):",
        (eType==SQLITE_INSERT) ? "INSERT" :
        (eType==SQLITE_DELETE ? "DELETE" : "UPDATE"),
        bIndirect
    );
    p += 2;

    if( pParse->bPatchset==0 && eType==SQLITE_UPDATE ){
      fuzzPrintRecord(pGrp, &p, 0);
    }
    fuzzPrintRecord(pGrp, &p, eType==SQLITE_DELETE && pParse->bPatchset);
    printf("\n");
  }
}