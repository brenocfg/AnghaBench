#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int nExtra; int iVersionMadeBy; int iVersionExtract; int flags; int iCompression; int mTime; int mDate; int nFile; int nComment; int iDiskStart; int iInternalAttr; int /*<<< orphan*/  zFile; int /*<<< orphan*/  iOffset; int /*<<< orphan*/  iExternalAttr; int /*<<< orphan*/  szUncompressed; int /*<<< orphan*/  szCompressed; int /*<<< orphan*/  crc32; } ;
struct TYPE_4__ {int /*<<< orphan*/  mUnixTime; int /*<<< orphan*/  aExtra; TYPE_2__ cds; } ;
typedef  TYPE_1__ ZipfileEntry ;
typedef  TYPE_2__ ZipfileCDS ;

/* Variables and functions */
 size_t ZIPFILE_CDS_NFILE_OFF ; 
 int ZIPFILE_EXTRA_TIMESTAMP ; 
 int /*<<< orphan*/  ZIPFILE_SIGNATURE_CDS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zipfileWrite16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zipfileWrite32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zipfileSerializeCDS(ZipfileEntry *pEntry, u8 *aBuf){
  u8 *a = aBuf;
  ZipfileCDS *pCDS = &pEntry->cds;

  if( pEntry->aExtra==0 ){
    pCDS->nExtra = 9;
  }

  zipfileWrite32(a, ZIPFILE_SIGNATURE_CDS);
  zipfileWrite16(a, pCDS->iVersionMadeBy);
  zipfileWrite16(a, pCDS->iVersionExtract);
  zipfileWrite16(a, pCDS->flags);
  zipfileWrite16(a, pCDS->iCompression);
  zipfileWrite16(a, pCDS->mTime);
  zipfileWrite16(a, pCDS->mDate);
  zipfileWrite32(a, pCDS->crc32);
  zipfileWrite32(a, pCDS->szCompressed);
  zipfileWrite32(a, pCDS->szUncompressed);
  assert( a==&aBuf[ZIPFILE_CDS_NFILE_OFF] );
  zipfileWrite16(a, pCDS->nFile);
  zipfileWrite16(a, pCDS->nExtra);
  zipfileWrite16(a, pCDS->nComment);
  zipfileWrite16(a, pCDS->iDiskStart);
  zipfileWrite16(a, pCDS->iInternalAttr);
  zipfileWrite32(a, pCDS->iExternalAttr);
  zipfileWrite32(a, pCDS->iOffset);

  memcpy(a, pCDS->zFile, pCDS->nFile);
  a += pCDS->nFile;

  if( pEntry->aExtra ){
    int n = (int)pCDS->nExtra + (int)pCDS->nComment;
    memcpy(a, pEntry->aExtra, n);
    a += n;
  }else{
    assert( pCDS->nExtra==9 );
    zipfileWrite16(a, ZIPFILE_EXTRA_TIMESTAMP);
    zipfileWrite16(a, 5);
    *a++ = 0x01;
    zipfileWrite32(a, pEntry->mUnixTime);
  }

  return a-aBuf;
}