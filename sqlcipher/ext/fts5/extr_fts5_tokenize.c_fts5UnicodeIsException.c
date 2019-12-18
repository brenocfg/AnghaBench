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
struct TYPE_3__ {int nException; int* aiException; } ;
typedef  TYPE_1__ Unicode61Tokenizer ;

/* Variables and functions */

__attribute__((used)) static int fts5UnicodeIsException(Unicode61Tokenizer *p, int iCode){
  if( p->nException>0 ){
    int *a = p->aiException;
    int iLo = 0;
    int iHi = p->nException-1;

    while( iHi>=iLo ){
      int iTest = (iHi + iLo) / 2;
      if( iCode==a[iTest] ){
        return 1;
      }else if( iCode>a[iTest] ){
        iLo = iTest+1;
      }else{
        iHi = iTest-1;
      }
    }
  }

  return 0;
}