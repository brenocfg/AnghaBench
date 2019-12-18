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
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  LeavesReader ;
typedef  int /*<<< orphan*/  DataBuffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  leavesReaderDestroy (int /*<<< orphan*/ *) ; 
 int leavesReaderInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderReset (int /*<<< orphan*/ *) ; 
 int loadSegmentLeavesInt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loadSegmentLeaves(fulltext_vtab *v,
                             sqlite_int64 iStartLeaf, sqlite_int64 iEndLeaf,
                             const char *pTerm, int nTerm, int isPrefix,
                             DataBuffer *out){
  int rc;
  LeavesReader reader;

  assert( iStartLeaf<=iEndLeaf );
  rc = leavesReaderInit(v, 0, iStartLeaf, iEndLeaf, NULL, 0, &reader);
  if( rc!=SQLITE_OK ) return rc;

  rc = loadSegmentLeavesInt(v, &reader, pTerm, nTerm, isPrefix, out);
  leavesReaderReset(&reader);
  leavesReaderDestroy(&reader);
  return rc;
}