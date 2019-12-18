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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int nCol; int /*<<< orphan*/ * aiCol; } ;
typedef  TYPE_1__ Fts5Colset ;
typedef  int /*<<< orphan*/  Fts5Buffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  fts5BufferAppendBlob (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fts5BufferZero (int /*<<< orphan*/ *) ; 
 int fts5IndexExtractCol (int /*<<< orphan*/  const**,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5IndexExtractColset(
  int *pRc,
  Fts5Colset *pColset,            /* Colset to filter on */
  const u8 *pPos, int nPos,       /* Position list */
  Fts5Buffer *pBuf                /* Output buffer */
){
  if( *pRc==SQLITE_OK ){
    int i;
    fts5BufferZero(pBuf);
    for(i=0; i<pColset->nCol; i++){
      const u8 *pSub = pPos;
      int nSub = fts5IndexExtractCol(&pSub, nPos, pColset->aiCol[i]);
      if( nSub ){
        fts5BufferAppendBlob(pRc, pBuf, nSub, pSub);
      }
    }
  }
}