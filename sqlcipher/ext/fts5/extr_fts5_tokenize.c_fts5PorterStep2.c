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

__attribute__((used)) static int fts5PorterStep2(char *aBuf, int *pnBuf){
  int ret = 0;
  int nBuf = *pnBuf;
  switch( aBuf[nBuf-2] ){
    
    case 'a': 
      if( nBuf>7 && 0==memcmp("ational", &aBuf[nBuf-7], 7) ){
        if( fts5Porter_MGt0(aBuf, nBuf-7) ){
          memcpy(&aBuf[nBuf-7], "ate", 3);
          *pnBuf = nBuf - 7 + 3;
        }
      }else if( nBuf>6 && 0==memcmp("tional", &aBuf[nBuf-6], 6) ){
        if( fts5Porter_MGt0(aBuf, nBuf-6) ){
          memcpy(&aBuf[nBuf-6], "tion", 4);
          *pnBuf = nBuf - 6 + 4;
        }
      }
      break;
  
    case 'c': 
      if( nBuf>4 && 0==memcmp("enci", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "ence", 4);
          *pnBuf = nBuf - 4 + 4;
        }
      }else if( nBuf>4 && 0==memcmp("anci", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "ance", 4);
          *pnBuf = nBuf - 4 + 4;
        }
      }
      break;
  
    case 'e': 
      if( nBuf>4 && 0==memcmp("izer", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "ize", 3);
          *pnBuf = nBuf - 4 + 3;
        }
      }
      break;
  
    case 'g': 
      if( nBuf>4 && 0==memcmp("logi", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "log", 3);
          *pnBuf = nBuf - 4 + 3;
        }
      }
      break;
  
    case 'l': 
      if( nBuf>3 && 0==memcmp("bli", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt0(aBuf, nBuf-3) ){
          memcpy(&aBuf[nBuf-3], "ble", 3);
          *pnBuf = nBuf - 3 + 3;
        }
      }else if( nBuf>4 && 0==memcmp("alli", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "al", 2);
          *pnBuf = nBuf - 4 + 2;
        }
      }else if( nBuf>5 && 0==memcmp("entli", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "ent", 3);
          *pnBuf = nBuf - 5 + 3;
        }
      }else if( nBuf>3 && 0==memcmp("eli", &aBuf[nBuf-3], 3) ){
        if( fts5Porter_MGt0(aBuf, nBuf-3) ){
          memcpy(&aBuf[nBuf-3], "e", 1);
          *pnBuf = nBuf - 3 + 1;
        }
      }else if( nBuf>5 && 0==memcmp("ousli", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "ous", 3);
          *pnBuf = nBuf - 5 + 3;
        }
      }
      break;
  
    case 'o': 
      if( nBuf>7 && 0==memcmp("ization", &aBuf[nBuf-7], 7) ){
        if( fts5Porter_MGt0(aBuf, nBuf-7) ){
          memcpy(&aBuf[nBuf-7], "ize", 3);
          *pnBuf = nBuf - 7 + 3;
        }
      }else if( nBuf>5 && 0==memcmp("ation", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "ate", 3);
          *pnBuf = nBuf - 5 + 3;
        }
      }else if( nBuf>4 && 0==memcmp("ator", &aBuf[nBuf-4], 4) ){
        if( fts5Porter_MGt0(aBuf, nBuf-4) ){
          memcpy(&aBuf[nBuf-4], "ate", 3);
          *pnBuf = nBuf - 4 + 3;
        }
      }
      break;
  
    case 's': 
      if( nBuf>5 && 0==memcmp("alism", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "al", 2);
          *pnBuf = nBuf - 5 + 2;
        }
      }else if( nBuf>7 && 0==memcmp("iveness", &aBuf[nBuf-7], 7) ){
        if( fts5Porter_MGt0(aBuf, nBuf-7) ){
          memcpy(&aBuf[nBuf-7], "ive", 3);
          *pnBuf = nBuf - 7 + 3;
        }
      }else if( nBuf>7 && 0==memcmp("fulness", &aBuf[nBuf-7], 7) ){
        if( fts5Porter_MGt0(aBuf, nBuf-7) ){
          memcpy(&aBuf[nBuf-7], "ful", 3);
          *pnBuf = nBuf - 7 + 3;
        }
      }else if( nBuf>7 && 0==memcmp("ousness", &aBuf[nBuf-7], 7) ){
        if( fts5Porter_MGt0(aBuf, nBuf-7) ){
          memcpy(&aBuf[nBuf-7], "ous", 3);
          *pnBuf = nBuf - 7 + 3;
        }
      }
      break;
  
    case 't': 
      if( nBuf>5 && 0==memcmp("aliti", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "al", 2);
          *pnBuf = nBuf - 5 + 2;
        }
      }else if( nBuf>5 && 0==memcmp("iviti", &aBuf[nBuf-5], 5) ){
        if( fts5Porter_MGt0(aBuf, nBuf-5) ){
          memcpy(&aBuf[nBuf-5], "ive", 3);
          *pnBuf = nBuf - 5 + 3;
        }
      }else if( nBuf>6 && 0==memcmp("biliti", &aBuf[nBuf-6], 6) ){
        if( fts5Porter_MGt0(aBuf, nBuf-6) ){
          memcpy(&aBuf[nBuf-6], "ble", 3);
          *pnBuf = nBuf - 6 + 3;
        }
      }
      break;
  
  }
  return ret;
}