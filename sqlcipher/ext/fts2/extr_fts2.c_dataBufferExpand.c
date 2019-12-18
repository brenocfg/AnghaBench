#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nData; scalar_t__ nCapacity; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ DataBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_realloc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dataBufferExpand(DataBuffer *pBuffer, int nAddCapacity){
  assert( nAddCapacity>0 );
  /* TODO(shess) Consider expanding more aggressively.  Note that the
  ** underlying malloc implementation may take care of such things for
  ** us already.
  */
  if( pBuffer->nData+nAddCapacity>pBuffer->nCapacity ){
    pBuffer->nCapacity = pBuffer->nData+nAddCapacity;
    pBuffer->pData = sqlite3_realloc(pBuffer->pData, pBuffer->nCapacity);
  }
}