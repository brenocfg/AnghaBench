#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_6__ {int ioError; } ;
struct TYPE_5__ {int op; int nByte; char* zBuf; scalar_t__ pNext; int /*<<< orphan*/ * pFileData; int /*<<< orphan*/  iOffset; } ;
typedef  TYPE_1__ AsyncWrite ;
typedef  int /*<<< orphan*/  AsyncFileData ;

/* Variables and functions */
 int ASYNC_CLOSE ; 
 int SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  addAsyncWrite (TYPE_1__*) ; 
 TYPE_3__ async ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_1__* sqlite3_malloc (int) ; 

__attribute__((used)) static int addNewAsyncWrite(
  AsyncFileData *pFileData, 
  int op, 
  sqlite3_int64 iOffset, 
  int nByte,
  const char *zByte
){
  AsyncWrite *p;
  if( op!=ASYNC_CLOSE && async.ioError ){
    return async.ioError;
  }
  p = sqlite3_malloc(sizeof(AsyncWrite) + (zByte?nByte:0));
  if( !p ){
    /* The upper layer does not expect operations like OsWrite() to
    ** return SQLITE_NOMEM. This is partly because under normal conditions
    ** SQLite is required to do rollback without calling malloc(). So
    ** if malloc() fails here, treat it as an I/O error. The above
    ** layer knows how to handle that.
    */
    return SQLITE_IOERR;
  }
  p->op = op;
  p->iOffset = iOffset;
  p->nByte = nByte;
  p->pFileData = pFileData;
  p->pNext = 0;
  if( zByte ){
    p->zBuf = (char *)&p[1];
    memcpy(p->zBuf, zByte, nByte);
  }else{
    p->zBuf = 0;
  }
  addAsyncWrite(p);
  return SQLITE_OK;
}