#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* aBuf; int (* xToken ) (int /*<<< orphan*/ ,int,char*,int,int,int) ;int /*<<< orphan*/  pCtx; } ;
typedef  TYPE_1__ PorterContext ;

/* Variables and functions */
 int FTS5_PORTER_MAX_TOKEN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fts5PorterIsVowel (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts5PorterStep1A (char*,int*) ; 
 scalar_t__ fts5PorterStep1B (char*,int*) ; 
 scalar_t__ fts5PorterStep1B2 (char*,int*) ; 
 int /*<<< orphan*/  fts5PorterStep2 (char*,int*) ; 
 int /*<<< orphan*/  fts5PorterStep3 (char*,int*) ; 
 int /*<<< orphan*/  fts5PorterStep4 (char*,int*) ; 
 scalar_t__ fts5Porter_MEq1 (char*,int) ; 
 scalar_t__ fts5Porter_MGt1 (char*,int) ; 
 scalar_t__ fts5Porter_Ostar (char*,int) ; 
 scalar_t__ fts5Porter_Vowel (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,char const*,int,int,int) ; 

__attribute__((used)) static int fts5PorterCb(
  void *pCtx, 
  int tflags,
  const char *pToken, 
  int nToken, 
  int iStart, 
  int iEnd
){
  PorterContext *p = (PorterContext*)pCtx;

  char *aBuf;
  int nBuf;

  if( nToken>FTS5_PORTER_MAX_TOKEN || nToken<3 ) goto pass_through;
  aBuf = p->aBuf;
  nBuf = nToken;
  memcpy(aBuf, pToken, nBuf);

  /* Step 1. */
  fts5PorterStep1A(aBuf, &nBuf);
  if( fts5PorterStep1B(aBuf, &nBuf) ){
    if( fts5PorterStep1B2(aBuf, &nBuf)==0 ){
      char c = aBuf[nBuf-1];
      if( fts5PorterIsVowel(c, 0)==0 
       && c!='l' && c!='s' && c!='z' && c==aBuf[nBuf-2] 
      ){
        nBuf--;
      }else if( fts5Porter_MEq1(aBuf, nBuf) && fts5Porter_Ostar(aBuf, nBuf) ){
        aBuf[nBuf++] = 'e';
      }
    }
  }

  /* Step 1C. */
  if( aBuf[nBuf-1]=='y' && fts5Porter_Vowel(aBuf, nBuf-1) ){
    aBuf[nBuf-1] = 'i';
  }

  /* Steps 2 through 4. */
  fts5PorterStep2(aBuf, &nBuf);
  fts5PorterStep3(aBuf, &nBuf);
  fts5PorterStep4(aBuf, &nBuf);

  /* Step 5a. */
  assert( nBuf>0 );
  if( aBuf[nBuf-1]=='e' ){
    if( fts5Porter_MGt1(aBuf, nBuf-1) 
     || (fts5Porter_MEq1(aBuf, nBuf-1) && !fts5Porter_Ostar(aBuf, nBuf-1))
    ){
      nBuf--;
    }
  }

  /* Step 5b. */
  if( nBuf>1 && aBuf[nBuf-1]=='l' 
   && aBuf[nBuf-2]=='l' && fts5Porter_MGt1(aBuf, nBuf-1) 
  ){
    nBuf--;
  }

  return p->xToken(p->pCtx, tflags, aBuf, nBuf, iStart, iEnd);

 pass_through:
  return p->xToken(p->pCtx, tflags, pToken, nToken, iStart, iEnd);
}