#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  scalar_t__ i64 ;
struct TYPE_17__ {int nn; int /*<<< orphan*/ * p; } ;
struct TYPE_16__ {int iLeafPgno; scalar_t__ bEof; char const* iRowid; int n; scalar_t__ p; TYPE_2__* pData; } ;
typedef  TYPE_1__ Fts5DlidxLvl ;
typedef  TYPE_2__ Fts5Data ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 scalar_t__ FTS5_AVERAGES_ROWID ; 
 int FTS5_CORRUPT ; 
 scalar_t__ FTS5_DATA_ZERO_PADDING ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5BufferAppendBlob (int*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5BufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  fts5DebugRowid (int*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  fts5DecodeAverages (int*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fts5DecodeDoclist (int*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5DecodePoslist (int*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5DecodeRowid (scalar_t__,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  fts5DecodeRowidList (int*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5DecodeStructure (int*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5DlidxLvlNext (TYPE_1__*) ; 
 int fts5GetU16 (int /*<<< orphan*/ *) ; 
 scalar_t__ fts5GetVarint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferAppendPrintf (int*,TYPE_1__*,char*,int,char const*) ; 
 int /*<<< orphan*/  sqlite3Fts5BufferSet (int*,TYPE_1__*,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ sqlite3Fts5MallocZero (int*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5DecodeFunction(
  sqlite3_context *pCtx,          /* Function call context */
  int nArg,                       /* Number of args (always 2) */
  sqlite3_value **apVal           /* Function arguments */
){
  i64 iRowid;                     /* Rowid for record being decoded */
  int iSegid,iHeight,iPgno,bDlidx;/* Rowid components */
  const u8 *aBlob; int n;         /* Record to decode */
  u8 *a = 0;
  Fts5Buffer s;                   /* Build up text to return here */
  int rc = SQLITE_OK;             /* Return code */
  sqlite3_int64 nSpace = 0;
  int eDetailNone = (sqlite3_user_data(pCtx)!=0);

  assert( nArg==2 );
  UNUSED_PARAM(nArg);
  memset(&s, 0, sizeof(Fts5Buffer));
  iRowid = sqlite3_value_int64(apVal[0]);

  /* Make a copy of the second argument (a blob) in aBlob[]. The aBlob[]
  ** copy is followed by FTS5_DATA_ZERO_PADDING 0x00 bytes, which prevents
  ** buffer overreads even if the record is corrupt.  */
  n = sqlite3_value_bytes(apVal[1]);
  aBlob = sqlite3_value_blob(apVal[1]);
  nSpace = n + FTS5_DATA_ZERO_PADDING;
  a = (u8*)sqlite3Fts5MallocZero(&rc, nSpace);
  if( a==0 ) goto decode_out;
  if( n>0 ) memcpy(a, aBlob, n);

  fts5DecodeRowid(iRowid, &iSegid, &bDlidx, &iHeight, &iPgno);

  fts5DebugRowid(&rc, &s, iRowid);
  if( bDlidx ){
    Fts5Data dlidx;
    Fts5DlidxLvl lvl;

    dlidx.p = a;
    dlidx.nn = n;

    memset(&lvl, 0, sizeof(Fts5DlidxLvl));
    lvl.pData = &dlidx;
    lvl.iLeafPgno = iPgno;

    for(fts5DlidxLvlNext(&lvl); lvl.bEof==0; fts5DlidxLvlNext(&lvl)){
      sqlite3Fts5BufferAppendPrintf(&rc, &s, 
          " %d(%lld)", lvl.iLeafPgno, lvl.iRowid
      );
    }
  }else if( iSegid==0 ){
    if( iRowid==FTS5_AVERAGES_ROWID ){
      fts5DecodeAverages(&rc, &s, a, n);
    }else{
      fts5DecodeStructure(&rc, &s, a, n);
    }
  }else if( eDetailNone ){
    Fts5Buffer term;              /* Current term read from page */
    int szLeaf;
    int iPgidxOff = szLeaf = fts5GetU16(&a[2]);
    int iTermOff;
    int nKeep = 0;
    int iOff;

    memset(&term, 0, sizeof(Fts5Buffer));

    /* Decode any entries that occur before the first term. */
    if( szLeaf<n ){
      iPgidxOff += fts5GetVarint32(&a[iPgidxOff], iTermOff);
    }else{
      iTermOff = szLeaf;
    }
    fts5DecodeRowidList(&rc, &s, &a[4], iTermOff-4);

    iOff = iTermOff;
    while( iOff<szLeaf ){
      int nAppend;

      /* Read the term data for the next term*/
      iOff += fts5GetVarint32(&a[iOff], nAppend);
      term.n = nKeep;
      fts5BufferAppendBlob(&rc, &term, nAppend, &a[iOff]);
      sqlite3Fts5BufferAppendPrintf(
          &rc, &s, " term=%.*s", term.n, (const char*)term.p
      );
      iOff += nAppend;

      /* Figure out where the doclist for this term ends */
      if( iPgidxOff<n ){
        int nIncr;
        iPgidxOff += fts5GetVarint32(&a[iPgidxOff], nIncr);
        iTermOff += nIncr;
      }else{
        iTermOff = szLeaf;
      }

      fts5DecodeRowidList(&rc, &s, &a[iOff], iTermOff-iOff);
      iOff = iTermOff;
      if( iOff<szLeaf ){
        iOff += fts5GetVarint32(&a[iOff], nKeep);
      }
    }

    fts5BufferFree(&term);
  }else{
    Fts5Buffer term;              /* Current term read from page */
    int szLeaf;                   /* Offset of pgidx in a[] */
    int iPgidxOff;
    int iPgidxPrev = 0;           /* Previous value read from pgidx */
    int iTermOff = 0;
    int iRowidOff = 0;
    int iOff;
    int nDoclist;

    memset(&term, 0, sizeof(Fts5Buffer));

    if( n<4 ){
      sqlite3Fts5BufferSet(&rc, &s, 7, (const u8*)"corrupt");
      goto decode_out;
    }else{
      iRowidOff = fts5GetU16(&a[0]);
      iPgidxOff = szLeaf = fts5GetU16(&a[2]);
      if( iPgidxOff<n ){
        fts5GetVarint32(&a[iPgidxOff], iTermOff);
      }else if( iPgidxOff>n ){
        rc = FTS5_CORRUPT;
        goto decode_out;
      }
    }

    /* Decode the position list tail at the start of the page */
    if( iRowidOff!=0 ){
      iOff = iRowidOff;
    }else if( iTermOff!=0 ){
      iOff = iTermOff;
    }else{
      iOff = szLeaf;
    }
    if( iOff>n ){
      rc = FTS5_CORRUPT;
      goto decode_out;
    }
    fts5DecodePoslist(&rc, &s, &a[4], iOff-4);

    /* Decode any more doclist data that appears on the page before the
    ** first term. */
    nDoclist = (iTermOff ? iTermOff : szLeaf) - iOff;
    if( nDoclist+iOff>n ){
      rc = FTS5_CORRUPT;
      goto decode_out;
    }
    fts5DecodeDoclist(&rc, &s, &a[iOff], nDoclist);

    while( iPgidxOff<n && rc==SQLITE_OK ){
      int bFirst = (iPgidxOff==szLeaf);     /* True for first term on page */
      int nByte;                            /* Bytes of data */
      int iEnd;
      
      iPgidxOff += fts5GetVarint32(&a[iPgidxOff], nByte);
      iPgidxPrev += nByte;
      iOff = iPgidxPrev;

      if( iPgidxOff<n ){
        fts5GetVarint32(&a[iPgidxOff], nByte);
        iEnd = iPgidxPrev + nByte;
      }else{
        iEnd = szLeaf;
      }
      if( iEnd>szLeaf ){
        rc = FTS5_CORRUPT;
        break;
      }

      if( bFirst==0 ){
        iOff += fts5GetVarint32(&a[iOff], nByte);
        if( nByte>term.n ){
          rc = FTS5_CORRUPT;
          break;
        }
        term.n = nByte;
      }
      iOff += fts5GetVarint32(&a[iOff], nByte);
      if( iOff+nByte>n ){
        rc = FTS5_CORRUPT;
        break;
      }
      fts5BufferAppendBlob(&rc, &term, nByte, &a[iOff]);
      iOff += nByte;

      sqlite3Fts5BufferAppendPrintf(
          &rc, &s, " term=%.*s", term.n, (const char*)term.p
      );
      iOff += fts5DecodeDoclist(&rc, &s, &a[iOff], iEnd-iOff);
    }

    fts5BufferFree(&term);
  }
  
 decode_out:
  sqlite3_free(a);
  if( rc==SQLITE_OK ){
    sqlite3_result_text(pCtx, (const char*)s.p, s.n, SQLITE_TRANSIENT);
  }else{
    sqlite3_result_error_code(pCtx, rc);
  }
  fts5BufferFree(&s);
}