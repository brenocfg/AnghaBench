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
 int /*<<< orphan*/  fts5Porter_MGt0 (char*,int) ; 
 int /*<<< orphan*/  fts5Porter_Vowel (char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int fts5PorterStep1B(char *aBuf, int *pnBuf){
  int ret = 0;
  int nBuf = *pnBuf;
  switch( aBuf[nBuf-2] ){
    
    case 'e': 
      if( nBuf>3 && 0==memcmp("eed", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt0(aBuf, nBuf-3) ){
          memcpy(&aBuf[nBuf-3], "ee", 2);
          *pnBuf = nBuf - 3 + 2;
        }
      }else if( nBuf>2 && 0==memcmp("ed", &aBuf[nBuf-2], 2) ){
        if( fts5Porter_Vowel(aBuf, nBuf-2) ){
          *pnBuf = nBuf - 2;
          ret = 1;
        }
      }
      break;
  
    case 'n': 
      if( nBuf>3 && 0==memcmp("ing", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_Vowel(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
          ret = 1;
        }
      }
      break;
  
  }
  return ret;
}