#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pBlob; struct TYPE_6__* aNode; struct TYPE_6__* zTerm; } ;
typedef  TYPE_1__ Fts3SegReader ;

/* Variables and functions */
 int /*<<< orphan*/  fts3SegReaderIsPending (TYPE_1__*) ; 
 int /*<<< orphan*/  fts3SegReaderIsRootOnly (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_blob_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

void sqlite3Fts3SegReaderFree(Fts3SegReader *pReader){
  if( pReader ){
    if( !fts3SegReaderIsPending(pReader) ){
      sqlite3_free(pReader->zTerm);
    }
    if( !fts3SegReaderIsRootOnly(pReader) ){
      sqlite3_free(pReader->aNode);
    }
    sqlite3_blob_close(pReader->pBlob);
  }
  sqlite3_free(pReader);
}