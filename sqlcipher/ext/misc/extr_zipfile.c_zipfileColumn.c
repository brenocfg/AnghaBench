#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_10__ {int /*<<< orphan*/ * pWriteFd; } ;
typedef  TYPE_4__ ZipfileTab ;
struct TYPE_9__ {TYPE_2__* pVtab; } ;
struct TYPE_11__ {int iId; TYPE_3__ base; TYPE_1__* pCurrent; int /*<<< orphan*/ * pFile; } ;
typedef  TYPE_5__ ZipfileCsr ;
struct TYPE_12__ {char* zFile; int iExternalAttr; int szUncompressed; int iCompression; int szCompressed; int /*<<< orphan*/  nFile; } ;
typedef  TYPE_6__ ZipfileCDS ;
struct TYPE_8__ {int /*<<< orphan*/  zErrMsg; } ;
struct TYPE_7__ {int mUnixTime; char* aData; int /*<<< orphan*/  iDataOff; TYPE_6__ cds; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_vtab_nochange (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zipfileInflate (int /*<<< orphan*/ *,char*,int,int) ; 
 int zipfileReadData (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zipfileColumn(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  ZipfileCsr *pCsr = (ZipfileCsr*)cur;
  ZipfileCDS *pCDS = &pCsr->pCurrent->cds;
  int rc = SQLITE_OK;
  switch( i ){
    case 0:   /* name */
      sqlite3_result_text(ctx, pCDS->zFile, -1, SQLITE_TRANSIENT);
      break;
    case 1:   /* mode */
      /* TODO: Whether or not the following is correct surely depends on
      ** the platform on which the archive was created.  */
      sqlite3_result_int(ctx, pCDS->iExternalAttr >> 16);
      break;
    case 2: { /* mtime */
      sqlite3_result_int64(ctx, pCsr->pCurrent->mUnixTime);
      break;
    }
    case 3: { /* sz */
      if( sqlite3_vtab_nochange(ctx)==0 ){
        sqlite3_result_int64(ctx, pCDS->szUncompressed);
      }
      break;
    }
    case 4:   /* rawdata */
      if( sqlite3_vtab_nochange(ctx) ) break;
    case 5: { /* data */
      if( i==4 || pCDS->iCompression==0 || pCDS->iCompression==8 ){
        int sz = pCDS->szCompressed;
        int szFinal = pCDS->szUncompressed;
        if( szFinal>0 ){
          u8 *aBuf;
          u8 *aFree = 0;
          if( pCsr->pCurrent->aData ){
            aBuf = pCsr->pCurrent->aData;
          }else{
            aBuf = aFree = sqlite3_malloc64(sz);
            if( aBuf==0 ){
              rc = SQLITE_NOMEM;
            }else{
              FILE *pFile = pCsr->pFile;
              if( pFile==0 ){
                pFile = ((ZipfileTab*)(pCsr->base.pVtab))->pWriteFd;
              }
              rc = zipfileReadData(pFile, aBuf, sz, pCsr->pCurrent->iDataOff,
                  &pCsr->base.pVtab->zErrMsg
              );
            }
          }
          if( rc==SQLITE_OK ){
            if( i==5 && pCDS->iCompression ){
              zipfileInflate(ctx, aBuf, sz, szFinal);
            }else{
              sqlite3_result_blob(ctx, aBuf, sz, SQLITE_TRANSIENT);
            }
          }
          sqlite3_free(aFree);
        }else{
          /* Figure out if this is a directory or a zero-sized file. Consider
          ** it to be a directory either if the mode suggests so, or if
          ** the final character in the name is '/'.  */
          u32 mode = pCDS->iExternalAttr >> 16;
          if( !(mode & S_IFDIR) && pCDS->zFile[pCDS->nFile-1]!='/' ){
            sqlite3_result_blob(ctx, "", 0, SQLITE_STATIC);
          }
        }
      }
      break;
    }
    case 6:   /* method */
      sqlite3_result_int(ctx, pCDS->iCompression);
      break;
    default:  /* z */
      assert( i==7 );
      sqlite3_result_int64(ctx, pCsr->iId);
      break;
  }

  return rc;
}