#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_14__ {scalar_t__ n; scalar_t__ nAlloc; int /*<<< orphan*/  a; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  n; int /*<<< orphan*/  a; } ;
struct TYPE_13__ {int /*<<< orphan*/  iChild; int /*<<< orphan*/  nDoclist; int /*<<< orphan*/  aDoclist; TYPE_1__ term; scalar_t__ aNode; } ;
typedef  TYPE_2__ NodeReader ;
typedef  TYPE_3__ Blob ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blobGrowBuffer (TYPE_3__*,int,int*) ; 
 int fts3AppendToNode (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts3StartNode (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int fts3TermCmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int nodeReaderInit (TYPE_2__*,char const*,int) ; 
 int nodeReaderNext (TYPE_2__*) ; 
 int /*<<< orphan*/  nodeReaderRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts3TruncateNode(
  const char *aNode,              /* Current node image */
  int nNode,                      /* Size of aNode in bytes */
  Blob *pNew,                     /* OUT: Write new node image here */
  const char *zTerm,              /* Omit all terms smaller than this */
  int nTerm,                      /* Size of zTerm in bytes */
  sqlite3_int64 *piBlock          /* OUT: Block number in next layer down */
){
  NodeReader reader;              /* Reader object */
  Blob prev = {0, 0, 0};          /* Previous term written to new node */
  int rc = SQLITE_OK;             /* Return code */
  int bLeaf = aNode[0]=='\0';     /* True for a leaf node */

  /* Allocate required output space */
  blobGrowBuffer(pNew, nNode, &rc);
  if( rc!=SQLITE_OK ) return rc;
  pNew->n = 0;

  /* Populate new node buffer */
  for(rc = nodeReaderInit(&reader, aNode, nNode); 
      rc==SQLITE_OK && reader.aNode; 
      rc = nodeReaderNext(&reader)
  ){
    if( pNew->n==0 ){
      int res = fts3TermCmp(reader.term.a, reader.term.n, zTerm, nTerm);
      if( res<0 || (bLeaf==0 && res==0) ) continue;
      fts3StartNode(pNew, (int)aNode[0], reader.iChild);
      *piBlock = reader.iChild;
    }
    rc = fts3AppendToNode(
        pNew, &prev, reader.term.a, reader.term.n,
        reader.aDoclist, reader.nDoclist
    );
    if( rc!=SQLITE_OK ) break;
  }
  if( pNew->n==0 ){
    fts3StartNode(pNew, (int)aNode[0], reader.iChild);
    *piBlock = reader.iChild;
  }
  assert( pNew->n<=pNew->nAlloc );

  nodeReaderRelease(&reader);
  sqlite3_free(prev.a);
  return rc;
}