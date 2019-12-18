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
struct TYPE_4__ {scalar_t__ xCodec; int /*<<< orphan*/  xGet; scalar_t__ errCode; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ USEFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  getPageError ; 
 int /*<<< orphan*/  getPageMMap ; 
 int /*<<< orphan*/  getPageNormal ; 

__attribute__((used)) static void setGetterMethod(Pager *pPager){
  if( pPager->errCode ){
    pPager->xGet = getPageError;
#if SQLITE_MAX_MMAP_SIZE>0
  }else if( USEFETCH(pPager)
#ifdef SQLITE_HAS_CODEC
   && pPager->xCodec==0
#endif
  ){
    pPager->xGet = getPageMMap;
#endif /* SQLITE_MAX_MMAP_SIZE>0 */
  }else{
    pPager->xGet = getPageNormal;
  }
}