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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_6__ {int iLastPos; scalar_t__ iLastColumn; TYPE_1__* pDoclist; int /*<<< orphan*/  p; } ;
struct TYPE_5__ {scalar_t__ iType; } ;
typedef  TYPE_2__ DocListReader ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atEnd (TYPE_2__*) ; 
 scalar_t__ getVarint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite_int64 readDocid(DocListReader *pReader){
  sqlite_int64 ret;
  assert( !atEnd(pReader) );
  assert( pReader->iLastPos==-1 );
  pReader->p += getVarint(pReader->p, &ret);
  if( pReader->pDoclist->iType>=DL_POSITIONS ){
    pReader->iLastColumn = 0;
    pReader->iLastPos = 0;
  }
  return ret;
}