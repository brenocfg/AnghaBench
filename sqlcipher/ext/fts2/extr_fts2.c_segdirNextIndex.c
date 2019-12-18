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

/* Variables and functions */
 int MERGE_COUNT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int segdir_max_index (int /*<<< orphan*/ *,int,int*) ; 
 int segmentMerge (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int segdirNextIndex(fulltext_vtab *v, int iLevel, int *pidx){
  int rc = segdir_max_index(v, iLevel, pidx);
  if( rc==SQLITE_DONE ){              /* No segments at iLevel. */
    *pidx = 0;
  }else if( rc==SQLITE_ROW ){
    if( *pidx==(MERGE_COUNT-1) ){
      rc = segmentMerge(v, iLevel);
      if( rc!=SQLITE_OK ) return rc;
      *pidx = 0;
    }else{
      (*pidx)++;
    }
  }else{
    return rc;
  }
  return SQLITE_OK;
}