#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_5__ {int nData; char* pData; } ;
struct TYPE_6__ {int /*<<< orphan*/  parentWriter; scalar_t__ iEndBlockid; int /*<<< orphan*/  has_parent; TYPE_1__ data; } ;
typedef  TYPE_2__ LeafWriter ;

/* Variables and functions */
 int ROOT_MAX ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int interiorWriterRootInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int*,scalar_t__*) ; 
 int leafWriterFlush (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int leafWriterRootInfo(fulltext_vtab *v, LeafWriter *pWriter,
                              char **ppRootInfo, int *pnRootInfo,
                              sqlite_int64 *piEndBlockid){
  /* we can fit the segment entirely inline */
  if( !pWriter->has_parent && pWriter->data.nData<ROOT_MAX ){
    *ppRootInfo = pWriter->data.pData;
    *pnRootInfo = pWriter->data.nData;
    *piEndBlockid = 0;
    return SQLITE_OK;
  }

  /* Flush remaining leaf data. */
  if( pWriter->data.nData>0 ){
    int rc = leafWriterFlush(v, pWriter);
    if( rc!=SQLITE_OK ) return rc;
  }

  /* We must have flushed a leaf at some point. */
  assert( pWriter->has_parent );

  /* Tenatively set the end leaf blockid as the end blockid.  If the
  ** interior node can be returned inline, this will be the final
  ** blockid, otherwise it will be overwritten by
  ** interiorWriterRootInfo().
  */
  *piEndBlockid = pWriter->iEndBlockid;

  return interiorWriterRootInfo(v, &pWriter->parentWriter,
                                ppRootInfo, pnRootInfo, piEndBlockid);
}