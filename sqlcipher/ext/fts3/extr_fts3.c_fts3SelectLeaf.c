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
typedef  int /*<<< orphan*/  Fts3Table ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts3GetVarint32 (char const*,int*) ; 
 int fts3ScanInteriorNode (char const*,int,char const*,int,scalar_t__*,scalar_t__*) ; 
 int sqlite3Fts3ReadBlock (int /*<<< orphan*/ *,scalar_t__,char**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 

__attribute__((used)) static int fts3SelectLeaf(
  Fts3Table *p,                   /* Virtual table handle */
  const char *zTerm,              /* Term to select leaves for */
  int nTerm,                      /* Size of term zTerm in bytes */
  const char *zNode,              /* Buffer containing segment interior node */
  int nNode,                      /* Size of buffer at zNode */
  sqlite3_int64 *piLeaf,          /* Selected leaf node */
  sqlite3_int64 *piLeaf2          /* Selected leaf node */
){
  int rc = SQLITE_OK;             /* Return code */
  int iHeight;                    /* Height of this node in tree */

  assert( piLeaf || piLeaf2 );

  fts3GetVarint32(zNode, &iHeight);
  rc = fts3ScanInteriorNode(zTerm, nTerm, zNode, nNode, piLeaf, piLeaf2);
  assert( !piLeaf2 || !piLeaf || rc!=SQLITE_OK || (*piLeaf<=*piLeaf2) );

  if( rc==SQLITE_OK && iHeight>1 ){
    char *zBlob = 0;              /* Blob read from %_segments table */
    int nBlob = 0;                /* Size of zBlob in bytes */

    if( piLeaf && piLeaf2 && (*piLeaf!=*piLeaf2) ){
      rc = sqlite3Fts3ReadBlock(p, *piLeaf, &zBlob, &nBlob, 0);
      if( rc==SQLITE_OK ){
        rc = fts3SelectLeaf(p, zTerm, nTerm, zBlob, nBlob, piLeaf, 0);
      }
      sqlite3_free(zBlob);
      piLeaf = 0;
      zBlob = 0;
    }

    if( rc==SQLITE_OK ){
      rc = sqlite3Fts3ReadBlock(p, piLeaf?*piLeaf:*piLeaf2, &zBlob, &nBlob, 0);
    }
    if( rc==SQLITE_OK ){
      rc = fts3SelectLeaf(p, zTerm, nTerm, zBlob, nBlob, piLeaf, piLeaf2);
    }
    sqlite3_free(zBlob);
  }

  return rc;
}