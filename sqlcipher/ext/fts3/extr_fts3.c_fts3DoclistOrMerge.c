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
typedef  scalar_t__ sqlite3_int64 ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 scalar_t__ DOCID_CMP (scalar_t__,scalar_t__) ; 
 scalar_t__ FTS3_BUFFER_PADDING ; 
 int FTS3_VARINT_MAX ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3GetDeltaVarint3 (char**,char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  fts3PoslistCopy (char**,char**) ; 
 int fts3PoslistMerge (char**,char**,char**) ; 
 int /*<<< orphan*/  fts3PutDeltaVarint3 (char**,int,scalar_t__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc64 (scalar_t__) ; 

__attribute__((used)) static int fts3DoclistOrMerge(
  int bDescDoclist,               /* True if arguments are desc */
  char *a1, int n1,               /* First doclist */
  char *a2, int n2,               /* Second doclist */
  char **paOut, int *pnOut        /* OUT: Malloc'd doclist */
){
  int rc = SQLITE_OK;
  sqlite3_int64 i1 = 0;
  sqlite3_int64 i2 = 0;
  sqlite3_int64 iPrev = 0;
  char *pEnd1 = &a1[n1];
  char *pEnd2 = &a2[n2];
  char *p1 = a1;
  char *p2 = a2;
  char *p;
  char *aOut;
  int bFirstOut = 0;

  *paOut = 0;
  *pnOut = 0;

  /* Allocate space for the output. Both the input and output doclists
  ** are delta encoded. If they are in ascending order (bDescDoclist==0),
  ** then the first docid in each list is simply encoded as a varint. For
  ** each subsequent docid, the varint stored is the difference between the
  ** current and previous docid (a positive number - since the list is in
  ** ascending order).
  **
  ** The first docid written to the output is therefore encoded using the 
  ** same number of bytes as it is in whichever of the input lists it is
  ** read from. And each subsequent docid read from the same input list 
  ** consumes either the same or less bytes as it did in the input (since
  ** the difference between it and the previous value in the output must
  ** be a positive value less than or equal to the delta value read from 
  ** the input list). The same argument applies to all but the first docid
  ** read from the 'other' list. And to the contents of all position lists
  ** that will be copied and merged from the input to the output.
  **
  ** However, if the first docid copied to the output is a negative number,
  ** then the encoding of the first docid from the 'other' input list may
  ** be larger in the output than it was in the input (since the delta value
  ** may be a larger positive integer than the actual docid).
  **
  ** The space required to store the output is therefore the sum of the
  ** sizes of the two inputs, plus enough space for exactly one of the input
  ** docids to grow. 
  **
  ** A symetric argument may be made if the doclists are in descending 
  ** order.
  */
  aOut = sqlite3_malloc64((i64)n1+n2+FTS3_VARINT_MAX-1+FTS3_BUFFER_PADDING);
  if( !aOut ) return SQLITE_NOMEM;

  p = aOut;
  fts3GetDeltaVarint3(&p1, pEnd1, 0, &i1);
  fts3GetDeltaVarint3(&p2, pEnd2, 0, &i2);
  while( p1 || p2 ){
    sqlite3_int64 iDiff = DOCID_CMP(i1, i2);

    if( p2 && p1 && iDiff==0 ){
      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i1);
      rc = fts3PoslistMerge(&p, &p1, &p2);
      if( rc ) break;
      fts3GetDeltaVarint3(&p1, pEnd1, bDescDoclist, &i1);
      fts3GetDeltaVarint3(&p2, pEnd2, bDescDoclist, &i2);
    }else if( !p2 || (p1 && iDiff<0) ){
      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i1);
      fts3PoslistCopy(&p, &p1);
      fts3GetDeltaVarint3(&p1, pEnd1, bDescDoclist, &i1);
    }else{
      fts3PutDeltaVarint3(&p, bDescDoclist, &iPrev, &bFirstOut, i2);
      fts3PoslistCopy(&p, &p2);
      fts3GetDeltaVarint3(&p2, pEnd2, bDescDoclist, &i2);
    }
  }

  if( rc!=SQLITE_OK ){
    sqlite3_free(aOut);
    p = aOut = 0;
  }else{
    assert( (p-aOut)<=n1+n2+FTS3_VARINT_MAX-1 );
    memset(&aOut[(p-aOut)], 0, FTS3_BUFFER_PADDING);
  }
  *paOut = aOut;
  *pnOut = (int)(p-aOut);
  return rc;
}