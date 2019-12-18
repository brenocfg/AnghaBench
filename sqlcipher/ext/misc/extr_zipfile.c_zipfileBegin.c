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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  scalar_t__ i64 ;
struct TYPE_5__ {int /*<<< orphan*/  zErrMsg; } ;
struct TYPE_6__ {scalar_t__ pWriteFd; scalar_t__ szOrig; scalar_t__ szCurrent; int /*<<< orphan*/  zFile; TYPE_1__ base; } ;
typedef  TYPE_2__ ZipfileTab ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zipfileCleanupTransaction (TYPE_2__*) ; 
 int zipfileLoadDirectory (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zipfileBegin(sqlite3_vtab *pVtab){
  ZipfileTab *pTab = (ZipfileTab*)pVtab;
  int rc = SQLITE_OK;

  assert( pTab->pWriteFd==0 );

  /* Open a write fd on the file. Also load the entire central directory
  ** structure into memory. During the transaction any new file data is 
  ** appended to the archive file, but the central directory is accumulated
  ** in main-memory until the transaction is committed.  */
  pTab->pWriteFd = fopen(pTab->zFile, "ab+");
  if( pTab->pWriteFd==0 ){
    pTab->base.zErrMsg = sqlite3_mprintf(
        "zipfile: failed to open file %s for writing", pTab->zFile
        );
    rc = SQLITE_ERROR;
  }else{
    fseek(pTab->pWriteFd, 0, SEEK_END);
    pTab->szCurrent = pTab->szOrig = (i64)ftell(pTab->pWriteFd);
    rc = zipfileLoadDirectory(pTab, 0, 0);
  }

  if( rc!=SQLITE_OK ){
    zipfileCleanupTransaction(pTab);
  }

  return rc;
}