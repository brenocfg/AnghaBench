#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_8__ {int (* xColumnText ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,scalar_t__*) ;int (* xTokenize ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {char const* zOpen; char const* zClose; size_t iOff; scalar_t__ zOut; scalar_t__ nIn; int /*<<< orphan*/ * zIn; int /*<<< orphan*/  iter; } ;
typedef  TYPE_1__ HighlightContext ;
typedef  TYPE_2__ Fts5ExtensionApi ;
typedef  int /*<<< orphan*/  Fts5Context ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int fts5CInstIterInit (TYPE_2__ const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5HighlightAppend (int*,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fts5HighlightCb ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,scalar_t__*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fts5HighlightFunction(
  const Fts5ExtensionApi *pApi,   /* API offered by current FTS version */
  Fts5Context *pFts,              /* First arg to pass to pApi functions */
  sqlite3_context *pCtx,          /* Context for returning result/error */
  int nVal,                       /* Number of values in apVal[] array */
  sqlite3_value **apVal           /* Array of trailing arguments */
){
  HighlightContext ctx;
  int rc;
  int iCol;

  if( nVal!=3 ){
    const char *zErr = "wrong number of arguments to function highlight()";
    sqlite3_result_error(pCtx, zErr, -1);
    return;
  }

  iCol = sqlite3_value_int(apVal[0]);
  memset(&ctx, 0, sizeof(HighlightContext));
  ctx.zOpen = (const char*)sqlite3_value_text(apVal[1]);
  ctx.zClose = (const char*)sqlite3_value_text(apVal[2]);
  rc = pApi->xColumnText(pFts, iCol, &ctx.zIn, &ctx.nIn);

  if( ctx.zIn ){
    if( rc==SQLITE_OK ){
      rc = fts5CInstIterInit(pApi, pFts, iCol, &ctx.iter);
    }

    if( rc==SQLITE_OK ){
      rc = pApi->xTokenize(pFts, ctx.zIn, ctx.nIn, (void*)&ctx,fts5HighlightCb);
    }
    fts5HighlightAppend(&rc, &ctx, &ctx.zIn[ctx.iOff], ctx.nIn - ctx.iOff);

    if( rc==SQLITE_OK ){
      sqlite3_result_text(pCtx, (const char*)ctx.zOut, -1, SQLITE_TRANSIENT);
    }
    sqlite3_free(ctx.zOut);
  }
  if( rc!=SQLITE_OK ){
    sqlite3_result_error_code(pCtx, rc);
  }
}