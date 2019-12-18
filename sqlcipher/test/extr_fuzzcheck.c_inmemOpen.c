#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_6__ {int /*<<< orphan*/ * pMethods; } ;
typedef  TYPE_1__ sqlite3_file ;
struct TYPE_7__ {TYPE_3__* pVFile; } ;
typedef  TYPE_2__ VHandle ;
struct TYPE_8__ {int /*<<< orphan*/  nRef; } ;
typedef  TYPE_3__ VFile ;

/* Variables and functions */
 int SQLITE_FULL ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  VHandleMethods ; 
 TYPE_3__* createVFile (char const*,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int inmemOpen(
  sqlite3_vfs *pVfs,
  const char *zFilename,
  sqlite3_file *pFile,
  int openFlags,
  int *pOutFlags
){
  VFile *pVFile = createVFile(zFilename, 0, (unsigned char*)"");
  VHandle *pHandle = (VHandle*)pFile;
  if( pVFile==0 ){
    return SQLITE_FULL;
  }
  pHandle->pVFile = pVFile;
  pVFile->nRef++;
  pFile->pMethods = &VHandleMethods;
  if( pOutFlags ) *pOutFlags = openFlags;
  return SQLITE_OK;
}