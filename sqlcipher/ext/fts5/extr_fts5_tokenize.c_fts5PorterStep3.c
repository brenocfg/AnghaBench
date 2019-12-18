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
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int fts5PorterStep3(char *aBuf, int *pnBuf){
  int ret = 0;
  int nBuf = *pnBuf;
  switch( aBuf[nBuf-2] ){
    
    case 'a': 
      if( nBuf>4 && 0==memcmp("ical", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "ic", 2);
          *pnBuf = nBuf - 4 + 2;
        }
      }
      break;
  
    case 's': 
      if( nBuf>4 && 0==memcmp("ness", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          *pnBuf = nBuf - 4;
        }
      }
      break;
  
    case 't': 
      if( nBuf>5 && 0==memcmp("icate", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "ic", 2);
          *pnBuf = nBuf - 5 + 2;
        }
      }else if( nBuf>5 && 0==memcmp("iciti", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "ic", 2);
          *pnBuf = nBuf - 5 + 2;
        }
      }
      break;
  
    case 'u': 
      if( nBuf>3 && 0==memcmp("ful", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt0(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
    case 'v': 
      if( nBuf>5 && 0==memcmp("ative", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          *pnBuf = nBuf - 5;
        }
      }
      break;
  
    case 'z': 
      if( nBuf>5 && 0==memcmp("alize", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "al", 2);
          *pnBuf = nBuf - 5 + 2;
        }
      }
      break;
  
  }
  return ret;
}