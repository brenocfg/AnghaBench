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
 char CCLASS_DIGIT ; 
 char CCLASS_L ; 
 unsigned char CCLASS_OTHER ; 
 char CCLASS_R ; 
 unsigned char CCLASS_SILENT ; 
 unsigned char CCLASS_SPACE ; 
 unsigned char CCLASS_VOWEL ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned char* className ; 
 unsigned char* initClass ; 
 unsigned char* midClass ; 
 unsigned char* sqlite3_malloc64 (int) ; 

__attribute__((used)) static unsigned char *phoneticHash(const unsigned char *zIn, int nIn){
  unsigned char *zOut = sqlite3_malloc64( nIn + 1 );
  int i;
  int nOut = 0;
  char cPrev = 0x77;
  char cPrevX = 0x77;
  const unsigned char *aClass = initClass;

  if( zOut==0 ) return 0;
  if( nIn>2 ){
    switch( zIn[0] ){
      case 'g': 
      case 'k': {
        if( zIn[1]=='n' ){ zIn++; nIn--; }
        break;
      }
    }
  }
  for(i=0; i<nIn; i++){
    unsigned char c = zIn[i];
    if( i+1<nIn ){
      if( c=='w' && zIn[i+1]=='r' ) continue;
      if( c=='d' && (zIn[i+1]=='j' || zIn[i+1]=='g') ) continue;
      if( i+2<nIn ){
        if( c=='t' && zIn[i+1]=='c' && zIn[i+2]=='h' ) continue;
      }
    }
    c = aClass[c&0x7f];
    if( c==CCLASS_SPACE ) continue;
    if( c==CCLASS_OTHER && cPrev!=CCLASS_DIGIT ) continue;
    aClass = midClass;
    if( c==CCLASS_VOWEL && (cPrevX==CCLASS_R || cPrevX==CCLASS_L) ){
       continue; /* No vowels beside L or R */ 
    }
    if( (c==CCLASS_R || c==CCLASS_L) && cPrevX==CCLASS_VOWEL ){
       nOut--;   /* No vowels beside L or R */
    }
    cPrev = c;
    if( c==CCLASS_SILENT ) continue;
    cPrevX = c;
    c = className[c];
    assert( nOut>=0 );
    if( nOut==0 || c!=zOut[nOut-1] ) zOut[nOut++] = c;
  }
  zOut[nOut] = 0;
  return zOut;
}