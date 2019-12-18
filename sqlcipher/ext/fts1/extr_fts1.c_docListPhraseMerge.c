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
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  DocListReader ;
typedef  int /*<<< orphan*/  DocList ;

/* Variables and functions */
 int /*<<< orphan*/  mergePosList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ nextDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void docListPhraseMerge(
  DocList *pLeft,    /* Doclist resulting from the words on the left */
  DocList *pRight,   /* Doclist for the next word to the right */
  DocList *pOut      /* Write the combined doclist here */
){
  DocListReader left, right;
  sqlite_int64 docidLeft, docidRight;

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
      mergePosList(&left, &right, docidLeft, pOut);
      docidLeft = nextDocid(&left);
      docidRight = nextDocid(&right);
    }
  }
}