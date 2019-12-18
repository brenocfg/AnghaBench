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
struct TYPE_4__ {scalar_t__ sz; unsigned char* a; } ;
typedef  TYPE_2__ VFile ;

/* Variables and functions */
 scalar_t__ MX_FILE_SZ ; 
 int SQLITE_FULL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned char* realloc (unsigned char*,int) ; 

__attribute__((used)) static int inmemWrite(
  sqlite3_file *pFile,   /* Write to this file */
  const void *pData,     /* Content to write */
  int iAmt,              /* bytes to write */
  sqlite3_int64 iOfst    /* Start writing here */
){
  VHandle *pHandle = (VHandle*)pFile;
  VFile *pVFile = pHandle->pVFile;
  if( iOfst+iAmt > pVFile->sz ){
    unsigned char *aNew;
    if( iOfst+iAmt >= MX_FILE_SZ ){
      return SQLITE_FULL;
    }
    aNew = realloc(pVFile->a, (int)(iOfst+iAmt));
    if( aNew==0 ){
      return SQLITE_FULL;
    }
    pVFile->a = aNew;
    if( iOfst > pVFile->sz ){
      memset(pVFile->a + pVFile->sz, 0, (int)(iOfst - pVFile->sz));
    }
    pVFile->sz = (int)(iOfst + iAmt);
  }
  memcpy(pVFile->a + iOfst, pData, iAmt);
  return SQLITE_OK;
}