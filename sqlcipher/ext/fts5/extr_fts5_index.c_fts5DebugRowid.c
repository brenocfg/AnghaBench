#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ i64 ;
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 scalar_t__ FTS5_AVERAGES_ROWID ; 
 int /*<<< orphan*/  fts5DecodeRowid (scalar_t__,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendPrintf (int*,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void fts5DebugRowid(int *pRc, Fts5Buffer *pBuf, i64 iKey){
  int iSegid, iHeight, iPgno, bDlidx;       /* Rowid compenents */
  fts5DecodeRowid(iKey, &iSegid, &bDlidx, &iHeight, &iPgno);

  if( iSegid==0 ){
    if( iKey==FTS5_AVERAGES_ROWID ){
      sqlite3Fts5BufferAppendPrintf(pRc, pBuf, "{averages} ");
    }else{
      sqlite3Fts5BufferAppendPrintf(pRc, pBuf, "{structure}");
    }
  }
  else{
    sqlite3Fts5BufferAppendPrintf(pRc, pBuf, "{%ssegid=%d h=%d pgno=%d}",
        bDlidx ? "dlidx " : "", iSegid, iHeight, iPgno
    );
  }
}