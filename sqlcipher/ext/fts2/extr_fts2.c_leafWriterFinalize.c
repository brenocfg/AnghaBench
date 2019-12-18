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
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  fulltext_vtab ;
struct TYPE_4__ {int /*<<< orphan*/  iEndBlockid; int /*<<< orphan*/  iStartBlockid; int /*<<< orphan*/  idx; int /*<<< orphan*/  iLevel; } ;
typedef  TYPE_1__ LeafWriter ;

/* Variables and functions */
 int SQLITE_OK ; 
 int leafWriterRootInfo (int /*<<< orphan*/ *,TYPE_1__*,char**,int*,scalar_t__*) ; 
 int segdir_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

__attribute__((used)) static int leafWriterFinalize(fulltext_vtab *v, LeafWriter *pWriter){
  sqlite_int64 iEndBlockid;
  char *pRootInfo;
  int rc, nRootInfo;

  rc = leafWriterRootInfo(v, pWriter, &pRootInfo, &nRootInfo, &iEndBlockid);
  if( rc!=SQLITE_OK ) return rc;

  /* Don't bother storing an entirely empty segment. */
  if( iEndBlockid==0 && nRootInfo==0 ) return SQLITE_OK;

  return segdir_set(v, pWriter->iLevel, pWriter->idx,
                    pWriter->iStartBlockid, pWriter->iEndBlockid,
                    iEndBlockid, pRootInfo, nRootInfo);
}