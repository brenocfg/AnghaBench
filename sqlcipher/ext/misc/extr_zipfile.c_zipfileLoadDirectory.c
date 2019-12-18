#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_13__ {int /*<<< orphan*/  pWriteFd; } ;
typedef  TYPE_2__ ZipfileTab ;
struct TYPE_12__ {scalar_t__ nComment; scalar_t__ nFile; scalar_t__ nExtra; } ;
struct TYPE_14__ {TYPE_1__ cds; } ;
typedef  TYPE_3__ ZipfileEntry ;
struct TYPE_15__ {int nEntry; int /*<<< orphan*/  iOffset; } ;
typedef  TYPE_4__ ZipfileEOCD ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ ZIPFILE_CDS_FIXED_SZ ; 
 int /*<<< orphan*/  zipfileAddEntry (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int zipfileGetEntry (TYPE_2__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int zipfileReadEOCD (TYPE_2__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int zipfileLoadDirectory(ZipfileTab *pTab, const u8 *aBlob, int nBlob){
  ZipfileEOCD eocd;
  int rc;
  int i;
  i64 iOff;

  rc = zipfileReadEOCD(pTab, aBlob, nBlob, pTab->pWriteFd, &eocd);
  iOff = eocd.iOffset;
  for(i=0; rc==SQLITE_OK && i<eocd.nEntry; i++){
    ZipfileEntry *pNew = 0;
    rc = zipfileGetEntry(pTab, aBlob, nBlob, pTab->pWriteFd, iOff, &pNew);

    if( rc==SQLITE_OK ){
      zipfileAddEntry(pTab, 0, pNew);
      iOff += ZIPFILE_CDS_FIXED_SZ;
      iOff += (int)pNew->cds.nExtra + pNew->cds.nFile + pNew->cds.nComment;
    }
  }
  return rc;
}