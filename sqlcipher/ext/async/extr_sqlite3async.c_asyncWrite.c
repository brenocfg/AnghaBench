#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_2__ {int /*<<< orphan*/ * pData; } ;
typedef  int /*<<< orphan*/  AsyncFileData ;
typedef  TYPE_1__ AsyncFile ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_WRITE ; 
 int addNewAsyncWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*) ; 

__attribute__((used)) static int asyncWrite(
  sqlite3_file *pFile, 
  const void *pBuf, 
  int amt, 
  sqlite3_int64 iOff
){
  AsyncFileData *p = ((AsyncFile *)pFile)->pData;
  return addNewAsyncWrite(p, ASYNC_WRITE, iOff, amt, pBuf);
}