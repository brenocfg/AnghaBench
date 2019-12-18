#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ aNode; scalar_t__ pBlob; } ;
typedef  TYPE_1__ Fts3SegReader ;

/* Variables and functions */
 int /*<<< orphan*/  fts3SegReaderIsRootOnly (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_blob_close (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 

__attribute__((used)) static void fts3SegReaderSetEof(Fts3SegReader *pSeg){
  if( !fts3SegReaderIsRootOnly(pSeg) ){
    sqlite3_free(pSeg->aNode);
    sqlite3_blob_close(pSeg->pBlob);
    pSeg->pBlob = 0;
  }
  pSeg->aNode = 0;
}