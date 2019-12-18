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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_6__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
typedef  int /*<<< orphan*/  multiplexGroup ;
struct TYPE_5__ {int (* xFileSize ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_2__* multiplexSubOpen (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite3_int64 multiplexSubSize(
  multiplexGroup *pGroup,    /* The multiplexor group */
  int iChunk,                /* Which chunk to open.  0==original file */
  int *rc                    /* Result code in and out */
){
  sqlite3_file *pSub;
  sqlite3_int64 sz = 0;

  if( *rc ) return 0;
  pSub = multiplexSubOpen(pGroup, iChunk, rc, NULL, 0);
  if( pSub==0 ) return 0;
  *rc = pSub->pMethods->xFileSize(pSub, &sz);
  return sz;
}