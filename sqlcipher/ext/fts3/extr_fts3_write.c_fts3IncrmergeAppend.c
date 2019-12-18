#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {char* zTerm; int nTerm; char* aDoclist; int nDoclist; } ;
struct TYPE_18__ {int nNodeSize; } ;
struct TYPE_17__ {int nLeafData; int /*<<< orphan*/  nWork; TYPE_1__* aNodeWriter; } ;
struct TYPE_15__ {scalar_t__ n; int /*<<< orphan*/  a; } ;
struct TYPE_14__ {int n; char* a; } ;
struct TYPE_16__ {TYPE_12__ key; TYPE_11__ block; int /*<<< orphan*/  iBlock; } ;
typedef  TYPE_1__ NodeWriter ;
typedef  TYPE_2__ IncrmergeWriter ;
typedef  TYPE_3__ Fts3Table ;
typedef  TYPE_4__ Fts3MultiSegReader ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  blobGrowBuffer (TYPE_11__*,int,int*) ; 
 int fts3AppendToNode (TYPE_11__*,TYPE_12__*,char const*,int,char const*,int) ; 
 int fts3IncrmergePush (TYPE_3__*,TYPE_2__*,char const*,int) ; 
 int fts3PrefixCompress (int /*<<< orphan*/ ,scalar_t__,char const*,int) ; 
 int fts3WriteSegment (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int sqlite3Fts3VarintLen (int) ; 

__attribute__((used)) static int fts3IncrmergeAppend(
  Fts3Table *p,                   /* Fts3 table handle */
  IncrmergeWriter *pWriter,       /* Writer object */
  Fts3MultiSegReader *pCsr        /* Cursor containing term and doclist */
){
  const char *zTerm = pCsr->zTerm;
  int nTerm = pCsr->nTerm;
  const char *aDoclist = pCsr->aDoclist;
  int nDoclist = pCsr->nDoclist;
  int rc = SQLITE_OK;           /* Return code */
  int nSpace;                   /* Total space in bytes required on leaf */
  int nPrefix;                  /* Size of prefix shared with previous term */
  int nSuffix;                  /* Size of suffix (nTerm - nPrefix) */
  NodeWriter *pLeaf;            /* Object used to write leaf nodes */

  pLeaf = &pWriter->aNodeWriter[0];
  nPrefix = fts3PrefixCompress(pLeaf->key.a, pLeaf->key.n, zTerm, nTerm);
  nSuffix = nTerm - nPrefix;

  nSpace  = sqlite3Fts3VarintLen(nPrefix);
  nSpace += sqlite3Fts3VarintLen(nSuffix) + nSuffix;
  nSpace += sqlite3Fts3VarintLen(nDoclist) + nDoclist;

  /* If the current block is not empty, and if adding this term/doclist
  ** to the current block would make it larger than Fts3Table.nNodeSize
  ** bytes, write this block out to the database. */
  if( pLeaf->block.n>0 && (pLeaf->block.n + nSpace)>p->nNodeSize ){
    rc = fts3WriteSegment(p, pLeaf->iBlock, pLeaf->block.a, pLeaf->block.n);
    pWriter->nWork++;

    /* Add the current term to the parent node. The term added to the 
    ** parent must:
    **
    **   a) be greater than the largest term on the leaf node just written
    **      to the database (still available in pLeaf->key), and
    **
    **   b) be less than or equal to the term about to be added to the new
    **      leaf node (zTerm/nTerm).
    **
    ** In other words, it must be the prefix of zTerm 1 byte longer than
    ** the common prefix (if any) of zTerm and pWriter->zTerm.
    */
    if( rc==SQLITE_OK ){
      rc = fts3IncrmergePush(p, pWriter, zTerm, nPrefix+1);
    }

    /* Advance to the next output block */
    pLeaf->iBlock++;
    pLeaf->key.n = 0;
    pLeaf->block.n = 0;

    nSuffix = nTerm;
    nSpace  = 1;
    nSpace += sqlite3Fts3VarintLen(nSuffix) + nSuffix;
    nSpace += sqlite3Fts3VarintLen(nDoclist) + nDoclist;
  }

  pWriter->nLeafData += nSpace;
  blobGrowBuffer(&pLeaf->block, pLeaf->block.n + nSpace, &rc);
  if( rc==SQLITE_OK ){
    if( pLeaf->block.n==0 ){
      pLeaf->block.n = 1;
      pLeaf->block.a[0] = '\0';
    }
    rc = fts3AppendToNode(
        &pLeaf->block, &pLeaf->key, zTerm, nTerm, aDoclist, nDoclist
    );
  }

  return rc;
}