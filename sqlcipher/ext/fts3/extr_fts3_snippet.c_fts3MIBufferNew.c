#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int sqlite3_int64 ;
struct TYPE_5__ {int* aMatchinfo; int nElem; char* zMatchinfo; int* aRef; } ;
typedef  TYPE_1__ MatchinfoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sqlite3_malloc64 (int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static MatchinfoBuffer *fts3MIBufferNew(size_t nElem, const char *zMatchinfo){
  MatchinfoBuffer *pRet;
  sqlite3_int64 nByte = sizeof(u32) * (2*(sqlite3_int64)nElem + 1)
                           + sizeof(MatchinfoBuffer);
  sqlite3_int64 nStr = strlen(zMatchinfo);

  pRet = sqlite3_malloc64(nByte + nStr+1);
  if( pRet ){
    memset(pRet, 0, nByte);
    pRet->aMatchinfo[0] = (u8*)(&pRet->aMatchinfo[1]) - (u8*)pRet;
    pRet->aMatchinfo[1+nElem] = pRet->aMatchinfo[0]
                                      + sizeof(u32)*((int)nElem+1);
    pRet->nElem = (int)nElem;
    pRet->zMatchinfo = ((char*)pRet) + nByte;
    memcpy(pRet->zMatchinfo, zMatchinfo, nStr+1);
    pRet->aRef[0] = 1;
  }

  return pRet;
}