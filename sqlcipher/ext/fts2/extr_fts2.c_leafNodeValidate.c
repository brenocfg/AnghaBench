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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VALID_DOCLIST (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DL_DEFAULT ; 
 int /*<<< orphan*/  assert (int) ; 
 int getVarint32 (char const*,int*) ; 

__attribute__((used)) static void leafNodeValidate(const char *pData, int nData){
  int n, iDummy;

  if( nData==0 ) return;
  assert( nData>0 );
  assert( pData!=0 );
  assert( pData+nData>pData );

  /* Must lead with a varint(0) */
  n = getVarint32(pData, &iDummy);
  assert( iDummy==0 );
  assert( n>0 );
  assert( n<nData );
  pData += n;
  nData -= n;

  /* Leading term length and data must fit in buffer. */
  n = getVarint32(pData, &iDummy);
  assert( n>0 );
  assert( iDummy>0 );
  assert( n+iDummy>0 );
  assert( n+iDummy<nData );
  pData += n+iDummy;
  nData -= n+iDummy;

  /* Leading term's doclist length and data must fit. */
  n = getVarint32(pData, &iDummy);
  assert( n>0 );
  assert( iDummy>0 );
  assert( n+iDummy>0 );
  assert( n+iDummy<=nData );
  ASSERT_VALID_DOCLIST(DL_DEFAULT, pData+n, iDummy, NULL);
  pData += n+iDummy;
  nData -= n+iDummy;

  /* Verify that trailing terms and doclists also are readable. */
  while( nData!=0 ){
    n = getVarint32(pData, &iDummy);
    assert( n>0 );
    assert( iDummy>=0 );
    assert( n<nData );
    pData += n;
    nData -= n;
    n = getVarint32(pData, &iDummy);
    assert( n>0 );
    assert( iDummy>0 );
    assert( n+iDummy>0 );
    assert( n+iDummy<nData );
    pData += n+iDummy;
    nData -= n+iDummy;

    n = getVarint32(pData, &iDummy);
    assert( n>0 );
    assert( iDummy>0 );
    assert( n+iDummy>0 );
    assert( n+iDummy<=nData );
    ASSERT_VALID_DOCLIST(DL_DEFAULT, pData+n, iDummy, NULL);
    pData += n+iDummy;
    nData -= n+iDummy;
  }
}