#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  iCsrId; int /*<<< orphan*/  iSpecial; int /*<<< orphan*/  ePlan; } ;
struct TYPE_7__ {int /*<<< orphan*/  zErrMsg; } ;
struct TYPE_8__ {TYPE_1__ base; int /*<<< orphan*/  pIndex; } ;
struct TYPE_9__ {TYPE_2__ p; } ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  FTS5_PLAN_SPECIAL ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3Fts5IndexReads (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int,char const*) ; 
 scalar_t__ sqlite3_strnicmp (char*,char const*,int) ; 

__attribute__((used)) static int fts5SpecialMatch(
  Fts5FullTable *pTab, 
  Fts5Cursor *pCsr, 
  const char *zQuery
){
  int rc = SQLITE_OK;             /* Return code */
  const char *z = zQuery;         /* Special query text */
  int n;                          /* Number of bytes in text at z */

  while( z[0]==' ' ) z++;
  for(n=0; z[n] && z[n]!=' '; n++);

  assert( pTab->p.base.zErrMsg==0 );
  pCsr->ePlan = FTS5_PLAN_SPECIAL;

  if( 0==sqlite3_strnicmp("reads", z, n) ){
    pCsr->iSpecial = sqlite3Fts5IndexReads(pTab->p.pIndex);
  }
  else if( 0==sqlite3_strnicmp("id", z, n) ){
    pCsr->iSpecial = pCsr->iCsrId;
  }
  else{
    /* An unrecognized directive. Return an error message. */
    pTab->p.base.zErrMsg = sqlite3_mprintf("unknown special query: %.*s", n, z);
    rc = SQLITE_ERROR;
  }

  return rc;
}