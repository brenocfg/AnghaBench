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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void fts3ReversePoslist(char *pStart, char **ppPoslist){
  char *p = &(*ppPoslist)[-2];
  char c = 0;

  /* Skip backwards passed any trailing 0x00 bytes added by NearTrim() */
  while( p>pStart && (c=*p--)==0 );

  /* Search backwards for a varint with value zero (the end of the previous 
  ** poslist). This is an 0x00 byte preceded by some byte that does not
  ** have the 0x80 bit set.  */
  while( p>pStart && (*p & 0x80) | c ){ 
    c = *p--; 
  }
  assert( p==pStart || c==0 );

  /* At this point p points to that preceding byte without the 0x80 bit
  ** set. So to find the start of the poslist, skip forward 2 bytes then
  ** over a varint. 
  **
  ** Normally. The other case is that p==pStart and the poslist to return
  ** is the first in the doclist. In this case do not skip forward 2 bytes.
  ** The second part of the if condition (c==0 && *ppPoslist>&p[2])
  ** is required for cases where the first byte of a doclist and the
  ** doclist is empty. For example, if the first docid is 10, a doclist
  ** that begins with:
  **
  **   0x0A 0x00 <next docid delta varint>
  */
  if( p>pStart || (c==0 && *ppPoslist>&p[2]) ){ p = &p[2]; }
  while( *p++&0x80 );
  *ppPoslist = p;
}