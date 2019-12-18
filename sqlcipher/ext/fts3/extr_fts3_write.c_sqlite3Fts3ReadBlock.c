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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_3__ {scalar_t__ zSegmentsTbl; scalar_t__ pSegments; int /*<<< orphan*/  zDb; int /*<<< orphan*/  db; int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ Fts3Table ;

/* Variables and functions */
 int FTS3_NODE_CHUNKSIZE ; 
 int FTS3_NODE_CHUNK_THRESHOLD ; 
 scalar_t__ FTS3_NODE_PADDING ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sqlite3_blob_bytes (scalar_t__) ; 
 int sqlite3_blob_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int sqlite3_blob_read (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_blob_reopen (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc (scalar_t__) ; 
 scalar_t__ sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 

int sqlite3Fts3ReadBlock(
  Fts3Table *p,                   /* FTS3 table handle */
  sqlite3_int64 iBlockid,         /* Access the row with blockid=$iBlockid */
  char **paBlob,                  /* OUT: Blob data in malloc'd buffer */
  int *pnBlob,                    /* OUT: Size of blob data */
  int *pnLoad                     /* OUT: Bytes actually loaded */
){
  int rc;                         /* Return code */

  /* pnBlob must be non-NULL. paBlob may be NULL or non-NULL. */
  assert( pnBlob );

  if( p->pSegments ){
    rc = sqlite3_blob_reopen(p->pSegments, iBlockid);
  }else{
    if( 0==p->zSegmentsTbl ){
      p->zSegmentsTbl = sqlite3_mprintf("%s_segments", p->zName);
      if( 0==p->zSegmentsTbl ) return SQLITE_NOMEM;
    }
    rc = sqlite3_blob_open(
       p->db, p->zDb, p->zSegmentsTbl, "block", iBlockid, 0, &p->pSegments
    );
  }

  if( rc==SQLITE_OK ){
    int nByte = sqlite3_blob_bytes(p->pSegments);
    *pnBlob = nByte;
    if( paBlob ){
      char *aByte = sqlite3_malloc(nByte + FTS3_NODE_PADDING);
      if( !aByte ){
        rc = SQLITE_NOMEM;
      }else{
        if( pnLoad && nByte>(FTS3_NODE_CHUNK_THRESHOLD) ){
          nByte = FTS3_NODE_CHUNKSIZE;
          *pnLoad = nByte;
        }
        rc = sqlite3_blob_read(p->pSegments, aByte, nByte, 0);
        memset(&aByte[nByte], 0, FTS3_NODE_PADDING);
        if( rc!=SQLITE_OK ){
          sqlite3_free(aByte);
          aByte = 0;
        }
      }
      *paBlob = aByte;
    }
  }

  return rc;
}