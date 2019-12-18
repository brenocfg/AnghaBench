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
 int /*<<< orphan*/  fts5Porter_MGt1 (char*,int) ; 
 int /*<<< orphan*/  fts5Porter_MGt1_and_S_or_T (char*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

__attribute__((used)) static int fts5PorterStep4(char *aBuf, int *pnBuf){
  int ret = 0;
  int nBuf = *pnBuf;
  switch( aBuf[nBuf-2] ){
    
    case 'a': 
      if( nBuf>2 && 0==memcmp("al", &aBuf[nBuf-2], 2) ){
        if( fts5Porter_MGt1(aBuf, nBuf-2) ){
          *pnBuf = nBuf - 2;
        }
      }
      break;
  
    case 'c': 
      if( nBuf>4 && 0==memcmp("ance", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt1(aBuf, nBuf-4) ){
          *pnBuf = nBuf - 4;
        }
      }else if( nBuf>4 && 0==memcmp("ence", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt1(aBuf, nBuf-4) ){
          *pnBuf = nBuf - 4;
        }
      }
      break;
  
    case 'e': 
      if( nBuf>2 && 0==memcmp("er", &aBuf[nBuf-2], 2) ){
        if( fts5Porter_MGt1(aBuf, nBuf-2) ){
          *pnBuf = nBuf - 2;
        }
      }
      break;
  
    case 'i': 
      if( nBuf>2 && 0==memcmp("ic", &aBuf[nBuf-2], 2) ){
        if( fts5Porter_MGt1(aBuf, nBuf-2) ){
          *pnBuf = nBuf - 2;
        }
      }
      break;
  
    case 'l': 
      if( nBuf>4 && 0==memcmp("able", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt1(aBuf, nBuf-4) ){
          *pnBuf = nBuf - 4;
        }
      }else if( nBuf>4 && 0==memcmp("ible", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt1(aBuf, nBuf-4) ){
          *pnBuf = nBuf - 4;
        }
      }
      break;
  
    case 'n': 
      if( nBuf>3 && 0==memcmp("ant", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }else if( nBuf>5 && 0==memcmp("ement", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt1(aBuf, nBuf-5) ){
          *pnBuf = nBuf - 5;
        }
      }else if( nBuf>4 && 0==memcmp("ment", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt1(aBuf, nBuf-4) ){
          *pnBuf = nBuf - 4;
        }
      }else if( nBuf>3 && 0==memcmp("ent", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
    case 'o': 
      if( nBuf>3 && 0==memcmp("ion", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1_and_S_or_T(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }else if( nBuf>2 && 0==memcmp("ou", &aBuf[nBuf-2], 2) ){
        if( fts5Porter_MGt1(aBuf, nBuf-2) ){
          *pnBuf = nBuf - 2;
        }
      }
      break;
  
    case 's': 
      if( nBuf>3 && 0==memcmp("ism", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
    case 't': 
      if( nBuf>3 && 0==memcmp("ate", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }else if( nBuf>3 && 0==memcmp("iti", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
    case 'u': 
      if( nBuf>3 && 0==memcmp("ous", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
    case 'v': 
      if( nBuf>3 && 0==memcmp("ive", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
    case 'z': 
      if( nBuf>3 && 0==memcmp("ize", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt1(aBuf, nBuf-3) ){
          *pnBuf = nBuf - 3;
        }
      }
      break;
  
  }
  return ret;
}