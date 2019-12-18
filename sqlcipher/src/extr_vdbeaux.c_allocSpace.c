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
struct ReusableSpace {void* pSpace; size_t nFree; int /*<<< orphan*/  nNeeded; } ;
typedef  size_t sqlite3_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  EIGHT_BYTE_ALIGNMENT (void*) ; 
 size_t ROUND8 (size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *allocSpace(
  struct ReusableSpace *p,  /* Bulk memory available for allocation */
  void *pBuf,               /* Pointer to a prior allocation */
  sqlite3_int64 nByte       /* Bytes of memory needed */
){
  assert( EIGHT_BYTE_ALIGNMENT(p->pSpace) );
  if( pBuf==0 ){
    nByte = ROUND8(nByte);
    if( nByte <= p->nFree ){
      p->nFree -= nByte;
      pBuf = &p->pSpace[p->nFree];
    }else{
      p->nNeeded += nByte;
    }
  }
  assert( EIGHT_BYTE_ALIGNMENT(pBuf) );
  return pBuf;
}