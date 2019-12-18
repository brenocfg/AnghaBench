#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* aPage; scalar_t__ zErr; } ;
typedef  TYPE_1__ GState ;

/* Variables and functions */
 int /*<<< orphan*/  ofstError (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  ofstPopPage (TYPE_1__*) ; 
 int /*<<< orphan*/  ofstPushPage (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ofstWalkInteriorPage (TYPE_1__*) ; 
 int /*<<< orphan*/  ofstWalkLeafPage (TYPE_1__*) ; 

__attribute__((used)) static void ofstWalkPage(GState *p, int pgno){
  if( p->zErr ) return;
  ofstPushPage(p, pgno);
  if( p->zErr ) return;
  if( p->aPage[0]==5 ){
    ofstWalkInteriorPage(p);
  }else if( p->aPage[0]==13 ){
    ofstWalkLeafPage(p);
  }else{
    ofstError(p, "page %d has a faulty type byte: %d", pgno, p->aPage[0]);
  }
  ofstPopPage(p);
}