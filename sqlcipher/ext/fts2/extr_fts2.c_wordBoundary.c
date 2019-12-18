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
struct snippetMatch {int iCol; int iStart; int nByte; } ;

/* Variables and functions */
 scalar_t__ safe_isspace (char const) ; 

__attribute__((used)) static int wordBoundary(
  int iBreak,                   /* The suggested break point */
  const char *zDoc,             /* Document text */
  int nDoc,                     /* Number of bytes in zDoc[] */
  struct snippetMatch *aMatch,  /* Matching words */
  int nMatch,                   /* Number of entries in aMatch[] */
  int iCol                      /* The column number for zDoc[] */
){
  int i;
  if( iBreak<=10 ){
    return 0;
  }
  if( iBreak>=nDoc-10 ){
    return nDoc;
  }
  for(i=0; i<nMatch && aMatch[i].iCol<iCol; i++){}
  while( i<nMatch && aMatch[i].iStart+aMatch[i].nByte<iBreak ){ i++; }
  if( i<nMatch ){
    if( aMatch[i].iStart<iBreak+10 ){
      return aMatch[i].iStart;
    }
    if( i>0 && aMatch[i-1].iStart+aMatch[i-1].nByte>=iBreak ){
      return aMatch[i-1].iStart;
    }
  }
  for(i=1; i<=10; i++){
    if( safe_isspace(zDoc[iBreak-i]) ){
      return iBreak - i + 1;
    }
    if( safe_isspace(zDoc[iBreak+i]) ){
      return iBreak + i + 1;
    }
  }
  return iBreak;
}