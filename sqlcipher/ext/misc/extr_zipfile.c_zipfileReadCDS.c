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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {void* iOffset; void* iExternalAttr; void* iInternalAttr; void* iDiskStart; void* nComment; void* nExtra; void* nFile; void* szUncompressed; void* szCompressed; void* crc32; void* mDate; void* mTime; void* iCompression; void* flags; void* iVersionExtract; void* iVersionMadeBy; } ;
typedef  TYPE_1__ ZipfileCDS ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 size_t ZIPFILE_CDS_FIXED_SZ ; 
 size_t ZIPFILE_CDS_NFILE_OFF ; 
 scalar_t__ ZIPFILE_SIGNATURE_CDS ; 
 int /*<<< orphan*/  assert (int) ; 
 void* zipfileRead16 (int /*<<< orphan*/ *) ; 
 void* zipfileRead32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zipfileReadCDS(u8 *aBuf, ZipfileCDS *pCDS){
  u8 *aRead = aBuf;
  u32 sig = zipfileRead32(aRead);
  int rc = SQLITE_OK;
  if( sig!=ZIPFILE_SIGNATURE_CDS ){
    rc = SQLITE_ERROR;
  }else{
    pCDS->iVersionMadeBy = zipfileRead16(aRead);
    pCDS->iVersionExtract = zipfileRead16(aRead);
    pCDS->flags = zipfileRead16(aRead);
    pCDS->iCompression = zipfileRead16(aRead);
    pCDS->mTime = zipfileRead16(aRead);
    pCDS->mDate = zipfileRead16(aRead);
    pCDS->crc32 = zipfileRead32(aRead);
    pCDS->szCompressed = zipfileRead32(aRead);
    pCDS->szUncompressed = zipfileRead32(aRead);
    assert( aRead==&aBuf[ZIPFILE_CDS_NFILE_OFF] );
    pCDS->nFile = zipfileRead16(aRead);
    pCDS->nExtra = zipfileRead16(aRead);
    pCDS->nComment = zipfileRead16(aRead);
    pCDS->iDiskStart = zipfileRead16(aRead);
    pCDS->iInternalAttr = zipfileRead16(aRead);
    pCDS->iExternalAttr = zipfileRead32(aRead);
    pCDS->iOffset = zipfileRead32(aRead);
    assert( aRead==&aBuf[ZIPFILE_CDS_FIXED_SZ] );
  }

  return rc;
}