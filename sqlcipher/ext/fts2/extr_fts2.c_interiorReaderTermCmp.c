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
typedef  int /*<<< orphan*/  InteriorReader ;

/* Variables and functions */
 char* interiorReaderTerm (int /*<<< orphan*/ *) ; 
 int interiorReaderTermBytes (int /*<<< orphan*/ *) ; 
 int memcmp (char const*,char const*,int) ; 

__attribute__((used)) static int interiorReaderTermCmp(InteriorReader *pReader,
                                 const char *pTerm, int nTerm, int isPrefix){
  const char *pReaderTerm = interiorReaderTerm(pReader);
  int nReaderTerm = interiorReaderTermBytes(pReader);
  int c, n = nReaderTerm<nTerm ? nReaderTerm : nTerm;

  if( n==0 ){
    if( nReaderTerm>0 ) return -1;
    if( nTerm>0 ) return 1;
    return 0;
  }

  c = memcmp(pReaderTerm, pTerm, n);
  if( c!=0 ) return c;
  if( isPrefix && n==nTerm ) return 0;
  return nReaderTerm - nTerm;
}