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
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_3__ {int nBuf; int /*<<< orphan*/ * aBuf; } ;
typedef  TYPE_1__ VfslogVfs ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,int) ; 
 int /*<<< orphan*/  put32bits (unsigned char*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  vfslog_flush (TYPE_1__*) ; 

__attribute__((used)) static void vfslog_string(sqlite3_vfs *pVfs, const char *zStr){
  VfslogVfs *p = (VfslogVfs *)pVfs;
  unsigned char *zRec;
  int nStr = zStr ? (int)strlen(zStr) : 0;
  if( (4+nStr+p->nBuf)>sizeof(p->aBuf) ){
    vfslog_flush(p);
  }
  zRec = (unsigned char *)&p->aBuf[p->nBuf];
  put32bits(&zRec[0], nStr);
  if( zStr ){
    memcpy(&zRec[4], zStr, nStr);
  }
  p->nBuf += (4 + nStr);
}