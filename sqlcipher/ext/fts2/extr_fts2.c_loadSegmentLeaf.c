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
typedef  int /*<<< orphan*/  fulltext_vtab ;
typedef  int /*<<< orphan*/  LeavesReader ;
typedef  int /*<<< orphan*/  DataBuffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  leavesReaderDestroy (int /*<<< orphan*/ *) ; 
 int leavesReaderInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  leavesReaderReset (int /*<<< orphan*/ *) ; 
 int loadSegmentLeavesInt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int loadSegmentLeaf(fulltext_vtab *v, const char *pData, int nData,
                           const char *pTerm, int nTerm, int isPrefix,
                           DataBuffer *out){
  LeavesReader reader;
  int rc;

  assert( nData>1 );
  assert( *pData=='\0' );
  rc = leavesReaderInit(v, 0, 0, 0, pData, nData, &reader);
  if( rc!=SQLITE_OK ) return rc;

  rc = loadSegmentLeavesInt(v, &reader, pTerm, nTerm, isPrefix, out);
  leavesReaderReset(&reader);
  leavesReaderDestroy(&reader);
  return rc;
}