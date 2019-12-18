#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_7__ {scalar_t__ iType; } ;
typedef  int /*<<< orphan*/  DocListReader ;
typedef  TYPE_1__ DocList ;

/* Variables and functions */
 scalar_t__ DL_POSITIONS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  docListAddDocid (TYPE_1__*,scalar_t__) ; 
 scalar_t__ nextDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerInit (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void docListAndMerge(
  DocList *pLeft,    /* Doclist resulting from the words on the left */
  DocList *pRight,   /* Doclist for the next word to the right */
  DocList *pOut      /* Write the combined doclist here */
){
  DocListReader left, right;
  sqlite_int64 docidLeft, docidRight;

  assert( pOut->iType<DL_POSITIONS );

  readerInit(&left, pLeft);
  readerInit(&right, pRight);
  docidLeft = nextDocid(&left);
  docidRight = nextDocid(&right);

  while( docidLeft>0 && docidRight>0 ){
    if( docidLeft<docidRight ){
      docidLeft = nextDocid(&left);
    }else if( docidRight<docidLeft ){
      docidRight = nextDocid(&right);
    }else{
      docListAddDocid(pOut, docidLeft);
      docidLeft = nextDocid(&left);
      docidRight = nextDocid(&right);
    }
  }
}