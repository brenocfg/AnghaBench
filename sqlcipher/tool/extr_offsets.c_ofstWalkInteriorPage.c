#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zErr; } ;
typedef  TYPE_1__ GState ;

/* Variables and functions */
 int ofst2byte (TYPE_1__*,int) ; 
 int ofst4byte (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ofstWalkPage (TYPE_1__*,int) ; 

__attribute__((used)) static void ofstWalkInteriorPage(GState *p){
  int nCell;
  int i;
  int ofst;
  int iChild;

  nCell = ofst2byte(p, 3);
  for(i=0; i<nCell; i++){
    ofst = ofst2byte(p, 12+i*2);
    iChild = ofst4byte(p, ofst);
    ofstWalkPage(p, iChild);
    if( p->zErr ) return;
  }
  ofstWalkPage(p, ofst4byte(p, 8));
}