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
struct TYPE_4__ {scalar_t__ sz; } ;
typedef  TYPE_2__ VFile ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int inmemTruncate(sqlite3_file *pFile, sqlite3_int64 iSize){
  VHandle *pHandle = (VHandle*)pFile;
  VFile *pVFile = pHandle->pVFile;
  if( pVFile->sz>iSize && iSize>=0 ) pVFile->sz = (int)iSize;
  return SQLITE_OK;
}