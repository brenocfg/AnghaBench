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
 int /*<<< orphan*/  docListAddDocid (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ nextDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readerInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void docListOrMerge(
  DocList *pLeft,    /* Doclist resulting from the words on the left */
  DocList *pRight,   /* Doclist for the next word to the right */
  DocList *pOut      /* Write the combined doclist here */
){
  DocListReader left, right;
  sqlite_int64 docidLeft, docidRight, priorLeft;

  readerInit(&left, pLeft);
  readerInit(&right, pRight);
  docidLeft = nextDocid(&left);
  docidRight = nextDocid(&right);

  while( docidLeft>0 && docidRight>0 ){
    if( docidLeft<=docidRight ){
      docListAddDocid(pOut, docidLeft);
    }else{
      docListAddDocid(pOut, docidRight);
    }
    priorLeft = docidLeft;
    if( docidLeft<=docidRight ){
      docidLeft = nextDocid(&left);
    }
    if( docidRight>0 && docidRight<=priorLeft ){
      docidRight = nextDocid(&right);
    }
  }
  while( docidLeft>0 ){
    docListAddDocid(pOut, docidLeft);
    docidLeft = nextDocid(&left);
  }
  while( docidRight>0 ){
    docListAddDocid(pOut, docidRight);
    docidRight = nextDocid(&right);
  }
}