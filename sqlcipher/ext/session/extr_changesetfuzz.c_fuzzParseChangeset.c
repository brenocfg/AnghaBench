#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct TYPE_6__ {int bPatchset; int nGroup; int /*<<< orphan*/ ** apGroup; } ;
typedef  int /*<<< orphan*/  FuzzChangesetGroup ;
typedef  TYPE_1__ FuzzChangeset ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fuzzParseChanges (char**,char*,TYPE_1__*) ; 
 int fuzzParseHeader (TYPE_1__*,char**,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_realloc64 (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int fuzzParseChangeset(
  u8 *pChangeset,                 /* Buffer containing changeset */
  int nChangeset,                 /* Size of buffer in bytes */
  FuzzChangeset *pParse           /* OUT: Results of parse */
){
  u8 *pEnd = &pChangeset[nChangeset];
  u8 *p = pChangeset;
  int rc = SQLITE_OK;

  memset(pParse, 0, sizeof(FuzzChangeset));
  if( nChangeset>0 ){
    pParse->bPatchset = (pChangeset[0]=='P');
  }

  while( rc==SQLITE_OK && p<pEnd ){
    FuzzChangesetGroup *pGrp = 0;

    /* Read a table-header from the changeset */
    rc = fuzzParseHeader(pParse, &p, pEnd, &pGrp);
    assert( (rc==SQLITE_OK)==(pGrp!=0) );

    /* If the table-header was successfully parsed, add the new change-group
    ** to the array and parse the associated changes. */
    if( rc==SQLITE_OK ){
      FuzzChangesetGroup **apNew = (FuzzChangesetGroup**)sqlite3_realloc64(
          pParse->apGroup, sizeof(FuzzChangesetGroup*)*(pParse->nGroup+1)
      );
      if( apNew==0 ){
        rc = SQLITE_NOMEM;
      }else{
        apNew[pParse->nGroup] = pGrp;
        pParse->apGroup = apNew;
        pParse->nGroup++;
      }
      rc = fuzzParseChanges(&p, pEnd, pParse);
    }
  }

  return rc;
}