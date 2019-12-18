#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  int u32 ;
typedef  void* u16 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  e ;
struct TYPE_10__ {int crc32; int szCompressed; int szUncompressed; int iExternalAttr; size_t iOffset; int nFile; char* zFile; void* iCompression; int /*<<< orphan*/  flags; int /*<<< orphan*/  iVersionExtract; int /*<<< orphan*/  iVersionMadeBy; } ;
struct TYPE_8__ {TYPE_5__ cds; scalar_t__ mUnixTime; } ;
typedef  TYPE_1__ ZipfileEntry ;
struct TYPE_11__ {size_t n; int /*<<< orphan*/ * a; } ;
struct TYPE_9__ {int /*<<< orphan*/  nEntry; TYPE_6__ cds; TYPE_6__ body; } ;
typedef  TYPE_2__ ZipfileCtx ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 scalar_t__ SQLITE_NULL ; 
 int SQLITE_OK ; 
 int ZIPFILE_CDS_FIXED_SZ ; 
 int ZIPFILE_LFH_FIXED_SZ ; 
 int /*<<< orphan*/  ZIPFILE_NEWENTRY_FLAGS ; 
 int /*<<< orphan*/  ZIPFILE_NEWENTRY_MADEBY ; 
 int /*<<< orphan*/  ZIPFILE_NEWENTRY_REQUIRED ; 
 int crc32 (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 char* sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int zipfileBufferGrow (TYPE_6__*,int) ; 
 int zipfileDeflate (char const*,int,char**,int*,char**) ; 
 int zipfileGetMode (int /*<<< orphan*/ *,int,int*,char**) ; 
 scalar_t__ zipfileGetTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zipfileMtimeToDos (TYPE_5__*,int) ; 
 scalar_t__ zipfileSerializeCDS (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zipfileSerializeLFH (TYPE_1__*,int /*<<< orphan*/ *) ; 

void zipfileStep(sqlite3_context *pCtx, int nVal, sqlite3_value **apVal){
  ZipfileCtx *p;                  /* Aggregate function context */
  ZipfileEntry e;                 /* New entry to add to zip archive */

  sqlite3_value *pName = 0;
  sqlite3_value *pMode = 0;
  sqlite3_value *pMtime = 0;
  sqlite3_value *pData = 0;
  sqlite3_value *pMethod = 0;

  int bIsDir = 0;
  u32 mode;
  int rc = SQLITE_OK;
  char *zErr = 0;

  int iMethod = -1;               /* Compression method to use (0 or 8) */

  const u8 *aData = 0;            /* Possibly compressed data for new entry */
  int nData = 0;                  /* Size of aData[] in bytes */
  int szUncompressed = 0;         /* Size of data before compression */
  u8 *aFree = 0;                  /* Free this before returning */
  u32 iCrc32 = 0;                 /* crc32 of uncompressed data */

  char *zName = 0;                /* Path (name) of new entry */
  int nName = 0;                  /* Size of zName in bytes */
  char *zFree = 0;                /* Free this before returning */
  int nByte;

  memset(&e, 0, sizeof(e));
  p = (ZipfileCtx*)sqlite3_aggregate_context(pCtx, sizeof(ZipfileCtx));
  if( p==0 ) return;

  /* Martial the arguments into stack variables */
  if( nVal!=2 && nVal!=4 && nVal!=5 ){
    zErr = sqlite3_mprintf("wrong number of arguments to function zipfile()");
    rc = SQLITE_ERROR;
    goto zipfile_step_out;
  }
  pName = apVal[0];
  if( nVal==2 ){
    pData = apVal[1];
  }else{
    pMode = apVal[1];
    pMtime = apVal[2];
    pData = apVal[3];
    if( nVal==5 ){
      pMethod = apVal[4];
    }
  }

  /* Check that the 'name' parameter looks ok. */
  zName = (char*)sqlite3_value_text(pName);
  nName = sqlite3_value_bytes(pName);
  if( zName==0 ){
    zErr = sqlite3_mprintf("first argument to zipfile() must be non-NULL");
    rc = SQLITE_ERROR;
    goto zipfile_step_out;
  }

  /* Inspect the 'method' parameter. This must be either 0 (store), 8 (use
  ** deflate compression) or NULL (choose automatically).  */
  if( pMethod && SQLITE_NULL!=sqlite3_value_type(pMethod) ){
    iMethod = (int)sqlite3_value_int64(pMethod);
    if( iMethod!=0 && iMethod!=8 ){
      zErr = sqlite3_mprintf("illegal method value: %d", iMethod);
      rc = SQLITE_ERROR;
      goto zipfile_step_out;
    }
  }

  /* Now inspect the data. If this is NULL, then the new entry must be a
  ** directory.  Otherwise, figure out whether or not the data should
  ** be deflated or simply stored in the zip archive. */
  if( sqlite3_value_type(pData)==SQLITE_NULL ){
    bIsDir = 1;
    iMethod = 0;
  }else{
    aData = sqlite3_value_blob(pData);
    szUncompressed = nData = sqlite3_value_bytes(pData);
    iCrc32 = crc32(0, aData, nData);
    if( iMethod<0 || iMethod==8 ){
      int nOut = 0;
      rc = zipfileDeflate(aData, nData, &aFree, &nOut, &zErr);
      if( rc!=SQLITE_OK ){
        goto zipfile_step_out;
      }
      if( iMethod==8 || nOut<nData ){
        aData = aFree;
        nData = nOut;
        iMethod = 8;
      }else{
        iMethod = 0;
      }
    }
  }

  /* Decode the "mode" argument. */
  rc = zipfileGetMode(pMode, bIsDir, &mode, &zErr);
  if( rc ) goto zipfile_step_out;

  /* Decode the "mtime" argument. */
  e.mUnixTime = zipfileGetTime(pMtime);

  /* If this is a directory entry, ensure that there is exactly one '/'
  ** at the end of the path. Or, if this is not a directory and the path
  ** ends in '/' it is an error. */
  if( bIsDir==0 ){
    if( zName[nName-1]=='/' ){
      zErr = sqlite3_mprintf("non-directory name must not end with /");
      rc = SQLITE_ERROR;
      goto zipfile_step_out;
    }
  }else{
    if( zName[nName-1]!='/' ){
      zName = zFree = sqlite3_mprintf("%s/", zName);
      nName++;
      if( zName==0 ){
        rc = SQLITE_NOMEM;
        goto zipfile_step_out;
      }
    }else{
      while( nName>1 && zName[nName-2]=='/' ) nName--;
    }
  }

  /* Assemble the ZipfileEntry object for the new zip archive entry */
  e.cds.iVersionMadeBy = ZIPFILE_NEWENTRY_MADEBY;
  e.cds.iVersionExtract = ZIPFILE_NEWENTRY_REQUIRED;
  e.cds.flags = ZIPFILE_NEWENTRY_FLAGS;
  e.cds.iCompression = (u16)iMethod;
  zipfileMtimeToDos(&e.cds, (u32)e.mUnixTime);
  e.cds.crc32 = iCrc32;
  e.cds.szCompressed = nData;
  e.cds.szUncompressed = szUncompressed;
  e.cds.iExternalAttr = (mode<<16);
  e.cds.iOffset = p->body.n;
  e.cds.nFile = (u16)nName;
  e.cds.zFile = zName;

  /* Append the LFH to the body of the new archive */
  nByte = ZIPFILE_LFH_FIXED_SZ + e.cds.nFile + 9;
  if( (rc = zipfileBufferGrow(&p->body, nByte)) ) goto zipfile_step_out;
  p->body.n += zipfileSerializeLFH(&e, &p->body.a[p->body.n]);

  /* Append the data to the body of the new archive */
  if( nData>0 ){
    if( (rc = zipfileBufferGrow(&p->body, nData)) ) goto zipfile_step_out;
    memcpy(&p->body.a[p->body.n], aData, nData);
    p->body.n += nData;
  }

  /* Append the CDS record to the directory of the new archive */
  nByte = ZIPFILE_CDS_FIXED_SZ + e.cds.nFile + 9;
  if( (rc = zipfileBufferGrow(&p->cds, nByte)) ) goto zipfile_step_out;
  p->cds.n += zipfileSerializeCDS(&e, &p->cds.a[p->cds.n]);

  /* Increment the count of entries in the archive */
  p->nEntry++;

 zipfile_step_out:
  sqlite3_free(aFree);
  sqlite3_free(zFree);
  if( rc ){
    if( zErr ){
      sqlite3_result_error(pCtx, zErr, -1);
    }else{
      sqlite3_result_error_code(pCtx, rc);
    }
  }
  sqlite3_free(zErr);
}