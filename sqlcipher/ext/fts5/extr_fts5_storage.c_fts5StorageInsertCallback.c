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
struct TYPE_4__ {scalar_t__ szCol; int /*<<< orphan*/  iCol; TYPE_1__* pStorage; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pIndex; } ;
typedef  TYPE_2__ Fts5InsertCtx ;
typedef  int /*<<< orphan*/  Fts5Index ;

/* Variables and functions */
 int FTS5_MAX_TOKEN_SIZE ; 
 int FTS5_TOKEN_COLOCATED ; 
 int /*<<< orphan*/  UNUSED_PARAM2 (int,int) ; 
 int sqlite3Fts5IndexWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char const*,int) ; 

__attribute__((used)) static int fts5StorageInsertCallback(
  void *pContext,                 /* Pointer to Fts5InsertCtx object */
  int tflags,
  const char *pToken,             /* Buffer containing token */
  int nToken,                     /* Size of token in bytes */
  int iUnused1,                   /* Start offset of token */
  int iUnused2                    /* End offset of token */
){
  Fts5InsertCtx *pCtx = (Fts5InsertCtx*)pContext;
  Fts5Index *pIdx = pCtx->pStorage->pIndex;
  UNUSED_PARAM2(iUnused1, iUnused2);
  if( nToken>FTS5_MAX_TOKEN_SIZE ) nToken = FTS5_MAX_TOKEN_SIZE;
  if( (tflags & FTS5_TOKEN_COLOCATED)==0 || pCtx->szCol==0 ){
    pCtx->szCol++;
  }
  return sqlite3Fts5IndexWrite(pIdx, pCtx->iCol, pCtx->szCol-1, pToken, nToken);
}