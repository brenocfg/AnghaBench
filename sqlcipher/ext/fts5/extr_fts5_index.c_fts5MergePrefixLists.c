#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  writer ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ i64 ;
struct TYPE_20__ {int n; int /*<<< orphan*/ * p; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {scalar_t__ iRowid; int nPoslist; size_t nSize; int /*<<< orphan*/ * aPoslist; int /*<<< orphan*/ * aEof; } ;
struct TYPE_18__ {scalar_t__ rc; } ;
typedef  int /*<<< orphan*/  Fts5PoslistWriter ;
typedef  TYPE_1__ Fts5Index ;
typedef  TYPE_2__ Fts5DoclistIter ;
typedef  TYPE_3__ Fts5Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_nc (int) ; 
 int /*<<< orphan*/  fts5BufferFree (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5BufferSafeAppendBlob (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fts5BufferSafeAppendVarint (TYPE_3__*,int) ; 
 int /*<<< orphan*/  fts5BufferSet (scalar_t__*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts5BufferZero (TYPE_3__*) ; 
 int /*<<< orphan*/  fts5DoclistIterInit (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  fts5DoclistIterNext (TYPE_2__*) ; 
 int /*<<< orphan*/  fts5MergeAppendDocid (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3Fts5BufferSize (scalar_t__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3Fts5PoslistNext64 (int /*<<< orphan*/ *,int,int*,scalar_t__*) ; 
 int /*<<< orphan*/  sqlite3Fts5PoslistSafeAppend (TYPE_3__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static void fts5MergePrefixLists(
  Fts5Index *p,                   /* FTS5 backend object */
  Fts5Buffer *p1,                 /* First list to merge */
  Fts5Buffer *p2                  /* Second list to merge */
){
  if( p2->n ){
    i64 iLastRowid = 0;
    Fts5DoclistIter i1;
    Fts5DoclistIter i2;
    Fts5Buffer out = {0, 0, 0};
    Fts5Buffer tmp = {0, 0, 0};

    /* The maximum size of the output is equal to the sum of the two 
    ** input sizes + 1 varint (9 bytes). The extra varint is because if the
    ** first rowid in one input is a large negative number, and the first in
    ** the other a non-negative number, the delta for the non-negative
    ** number will be larger on disk than the literal integer value
    ** was.  */
    if( sqlite3Fts5BufferSize(&p->rc, &out, p1->n + p2->n + 9) ) return;
    fts5DoclistIterInit(p1, &i1);
    fts5DoclistIterInit(p2, &i2);

    while( 1 ){
      if( i1.iRowid<i2.iRowid ){
        /* Copy entry from i1 */
        fts5MergeAppendDocid(&out, iLastRowid, i1.iRowid);
        fts5BufferSafeAppendBlob(&out, i1.aPoslist, i1.nPoslist+i1.nSize);
        fts5DoclistIterNext(&i1);
        if( i1.aPoslist==0 ) break;
      }
      else if( i2.iRowid!=i1.iRowid ){
        /* Copy entry from i2 */
        fts5MergeAppendDocid(&out, iLastRowid, i2.iRowid);
        fts5BufferSafeAppendBlob(&out, i2.aPoslist, i2.nPoslist+i2.nSize);
        fts5DoclistIterNext(&i2);
        if( i2.aPoslist==0 ) break;
      }
      else{
        /* Merge the two position lists. */ 
        i64 iPos1 = 0;
        i64 iPos2 = 0;
        int iOff1 = 0;
        int iOff2 = 0;
        u8 *a1 = &i1.aPoslist[i1.nSize];
        u8 *a2 = &i2.aPoslist[i2.nSize];
        int nCopy;
        u8 *aCopy;

        i64 iPrev = 0;
        Fts5PoslistWriter writer;
        memset(&writer, 0, sizeof(writer));

        fts5MergeAppendDocid(&out, iLastRowid, i2.iRowid);
        fts5BufferZero(&tmp);
        sqlite3Fts5BufferSize(&p->rc, &tmp, i1.nPoslist + i2.nPoslist);
        if( p->rc ) break;

        sqlite3Fts5PoslistNext64(a1, i1.nPoslist, &iOff1, &iPos1);
        sqlite3Fts5PoslistNext64(a2, i2.nPoslist, &iOff2, &iPos2);
        assert( iPos1>=0 && iPos2>=0 );

        if( iPos1<iPos2 ){
          sqlite3Fts5PoslistSafeAppend(&tmp, &iPrev, iPos1);
          sqlite3Fts5PoslistNext64(a1, i1.nPoslist, &iOff1, &iPos1);
        }else{
          sqlite3Fts5PoslistSafeAppend(&tmp, &iPrev, iPos2);
          sqlite3Fts5PoslistNext64(a2, i2.nPoslist, &iOff2, &iPos2);
        }

        if( iPos1>=0 && iPos2>=0 ){
          while( 1 ){
            if( iPos1<iPos2 ){
              if( iPos1!=iPrev ){
                sqlite3Fts5PoslistSafeAppend(&tmp, &iPrev, iPos1);
              }
              sqlite3Fts5PoslistNext64(a1, i1.nPoslist, &iOff1, &iPos1);
              if( iPos1<0 ) break;
            }else{
              assert_nc( iPos2!=iPrev );
              sqlite3Fts5PoslistSafeAppend(&tmp, &iPrev, iPos2);
              sqlite3Fts5PoslistNext64(a2, i2.nPoslist, &iOff2, &iPos2);
              if( iPos2<0 ) break;
            }
          }
        }

        if( iPos1>=0 ){
          if( iPos1!=iPrev ){
            sqlite3Fts5PoslistSafeAppend(&tmp, &iPrev, iPos1);
          }
          aCopy = &a1[iOff1];
          nCopy = i1.nPoslist - iOff1;
        }else{
          assert( iPos2>=0 && iPos2!=iPrev );
          sqlite3Fts5PoslistSafeAppend(&tmp, &iPrev, iPos2);
          aCopy = &a2[iOff2];
          nCopy = i2.nPoslist - iOff2;
        }
        if( nCopy>0 ){
          fts5BufferSafeAppendBlob(&tmp, aCopy, nCopy);
        }

        /* WRITEPOSLISTSIZE */
        fts5BufferSafeAppendVarint(&out, tmp.n * 2);
        fts5BufferSafeAppendBlob(&out, tmp.p, tmp.n);
        fts5DoclistIterNext(&i1);
        fts5DoclistIterNext(&i2);
        assert( out.n<=(p1->n+p2->n+9) );
        if( i1.aPoslist==0 || i2.aPoslist==0 ) break;
      }
    }

    if( i1.aPoslist ){
      fts5MergeAppendDocid(&out, iLastRowid, i1.iRowid);
      fts5BufferSafeAppendBlob(&out, i1.aPoslist, i1.aEof - i1.aPoslist);
    }
    else if( i2.aPoslist ){
      fts5MergeAppendDocid(&out, iLastRowid, i2.iRowid);
      fts5BufferSafeAppendBlob(&out, i2.aPoslist, i2.aEof - i2.aPoslist);
    }
    assert( out.n<=(p1->n+p2->n+9) );

    fts5BufferSet(&p->rc, p1, out.n, out.p);
    fts5BufferFree(&tmp);
    fts5BufferFree(&out);
  }
}