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
 scalar_t__ ALWAYS (char const) ; 
 scalar_t__ sqlite3StrICmp (char const*,char const*) ; 
 scalar_t__ sqlite3StrNICmp (char const*,char const*,int) ; 

int sqlite3MatchSpanName(
  const char *zSpan,
  const char *zCol,
  const char *zTab,
  const char *zDb
){
  int n;
  for(n=0; ALWAYS(zSpan[n]) && zSpan[n]!='.'; n++){}
  if( zDb && (sqlite3StrNICmp(zSpan, zDb, n)!=0 || zDb[n]!=0) ){
    return 0;
  }
  zSpan += n+1;
  for(n=0; ALWAYS(zSpan[n]) && zSpan[n]!='.'; n++){}
  if( zTab && (sqlite3StrNICmp(zSpan, zTab, n)!=0 || zTab[n]!=0) ){
    return 0;
  }
  zSpan += n+1;
  if( zCol && sqlite3StrICmp(zSpan, zCol)!=0 ){
    return 0;
  }
  return 1;
}