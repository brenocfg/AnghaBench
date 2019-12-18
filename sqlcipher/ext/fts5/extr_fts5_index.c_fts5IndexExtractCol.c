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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  fts5GetVarint32 (int const*,int) ; 

__attribute__((used)) static int fts5IndexExtractCol(
  const u8 **pa,                  /* IN/OUT: Pointer to poslist */
  int n,                          /* IN: Size of poslist in bytes */
  int iCol                        /* Column to extract from poslist */
){
  int iCurrent = 0;               /* Anything before the first 0x01 is col 0 */
  const u8 *p = *pa;
  const u8 *pEnd = &p[n];         /* One byte past end of position list */

  while( iCol>iCurrent ){
    /* Advance pointer p until it points to pEnd or an 0x01 byte that is
    ** not part of a varint. Note that it is not possible for a negative
    ** or extremely large varint to occur within an uncorrupted position 
    ** list. So the last byte of each varint may be assumed to have a clear
    ** 0x80 bit.  */
    while( *p!=0x01 ){
      while( *p++ & 0x80 );
      if( p>=pEnd ) return 0;
    }
    *pa = p++;
    iCurrent = *p++;
    if( iCurrent & 0x80 ){
      p--;
      p += fts5GetVarint32(p, iCurrent);
    }
  }
  if( iCol!=iCurrent ) return 0;

  /* Advance pointer p until it points to pEnd or an 0x01 byte that is
  ** not part of a varint */
  while( p<pEnd && *p!=0x01 ){
    while( *p++ & 0x80 );
  }

  return p - (*pa);
}