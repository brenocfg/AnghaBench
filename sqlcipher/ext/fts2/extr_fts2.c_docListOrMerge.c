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
typedef  int /*<<< orphan*/  DataBuffer ;
typedef  int /*<<< orphan*/  DLWriter ;
typedef  int /*<<< orphan*/  DLReader ;

/* Variables and functions */
 int /*<<< orphan*/  DL_DOCIDS ; 
 int /*<<< orphan*/  dataBufferAppend (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ dlrAtEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrDestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ dlrDocid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlrInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  dlrStep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwAdd (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dlwDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlwInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void docListOrMerge(
  const char *pLeft, int nLeft,
  const char *pRight, int nRight,
  DataBuffer *pOut      /* Write the combined doclist here */
){
  DLReader left, right;
  DLWriter writer;

  if( nLeft==0 ){
    if( nRight!=0 ) dataBufferAppend(pOut, pRight, nRight);
    return;
  }
  if( nRight==0 ){
    dataBufferAppend(pOut, pLeft, nLeft);
    return;
  }

  dlrInit(&left, DL_DOCIDS, pLeft, nLeft);
  dlrInit(&right, DL_DOCIDS, pRight, nRight);
  dlwInit(&writer, DL_DOCIDS, pOut);

  while( !dlrAtEnd(&left) || !dlrAtEnd(&right) ){
    if( dlrAtEnd(&right) ){
      dlwAdd(&writer, dlrDocid(&left));
      dlrStep(&left);
    }else if( dlrAtEnd(&left) ){
      dlwAdd(&writer, dlrDocid(&right));
      dlrStep(&right);
    }else if( dlrDocid(&left)<dlrDocid(&right) ){
      dlwAdd(&writer, dlrDocid(&left));
      dlrStep(&left);
    }else if( dlrDocid(&right)<dlrDocid(&left) ){
      dlwAdd(&writer, dlrDocid(&right));
      dlrStep(&right);
    }else{
      dlwAdd(&writer, dlrDocid(&left));
      dlrStep(&left);
      dlrStep(&right);
    }
  }

  dlrDestroy(&left);
  dlrDestroy(&right);
  dlwDestroy(&writer);
}