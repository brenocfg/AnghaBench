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
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static void lemon_addtext(
  char *zBuf,           /* The buffer to which text is added */
  int *pnUsed,          /* Slots of the buffer used so far */
  const char *zIn,      /* Text to add */
  int nIn,              /* Bytes of text to add.  -1 to use strlen() */
  int iWidth            /* Field width.  Negative to left justify */
){
  if( nIn<0 ) for(nIn=0; zIn[nIn]; nIn++){}
  while( iWidth>nIn ){ zBuf[(*pnUsed)++] = ' '; iWidth--; }
  if( nIn==0 ) return;
  memcpy(&zBuf[*pnUsed], zIn, nIn);
  *pnUsed += nIn;
  while( (-iWidth)>nIn ){ zBuf[(*pnUsed)++] = ' '; iWidth++; }
  zBuf[*pnUsed] = 0;
}