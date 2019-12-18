#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_3__ {TYPE_2__* pVFile; } ;
typedef  TYPE_1__ VHandle ;
struct TYPE_4__ {scalar_t__ sz; scalar_t__ a; } ;
typedef  TYPE_2__ VFile ;

/* Variables and functions */
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inmemRead(
  sqlite3_file *pFile,   /* Read from this open file */
  void *pData,           /* Store content in this buffer */
  int iAmt,              /* Bytes of content */
  sqlite3_int64 iOfst    /* Start reading here */
){
  VHandle *pHandle = (VHandle*)pFile;
  VFile *pVFile = pHandle->pVFile;
  if( iOfst<0 || iOfst>=pVFile->sz ){
    memset(pData, 0, iAmt);
    return SQLITE_IOERR_SHORT_READ;
  }
  if( iOfst+iAmt>pVFile->sz ){
    memset(pData, 0, iAmt);
    iAmt = (int)(pVFile->sz - iOfst);
    memcpy(pData, pVFile->a + iOfst, iAmt);
    return SQLITE_IOERR_SHORT_READ;
  }
  memcpy(pData, pVFile->a + iOfst, iAmt);
  return SQLITE_OK;
}