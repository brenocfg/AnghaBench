#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cFrom; scalar_t__ cTo3; scalar_t__ cTo2; scalar_t__ cTo1; } ;
typedef  TYPE_1__ Transliteration ;

/* Variables and functions */
 TYPE_1__* spellfixFindTranslit (int,int*) ; 
 int utf8Read (unsigned char const*,int,int*) ; 

__attribute__((used)) static int translen_to_charlen(const char *zIn, int nIn, int nTrans){
  int i, c, sz, nOut;
  int nChar;

  i = nOut = 0;
  for(nChar=0; i<nIn && nOut<nTrans; nChar++){
    c = utf8Read((const unsigned char *)&zIn[i], nIn-i, &sz);
    i += sz;

    nOut++;
    if( c>=128 ){
      int xTop, xBtm, x;
      const Transliteration *tbl = spellfixFindTranslit(c, &xTop);
      xBtm = 0;
      while( xTop>=xBtm ){
        x = (xTop + xBtm)/2;
        if( tbl[x].cFrom==c ){
          if( tbl[x].cTo1 ){
            nOut++;
            if( tbl[x].cTo2 ){
              nOut++;
              if( tbl[x].cTo3 ){
                nOut++;
              }
            }
          }
          break;
        }else if( tbl[x].cFrom>c ){
          xTop = x-1;
        }else{
          xBtm = x+1;
        }
      }
    }
  }

  return nChar;
}