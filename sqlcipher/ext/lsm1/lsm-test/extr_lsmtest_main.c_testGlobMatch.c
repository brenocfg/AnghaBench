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

int testGlobMatch(const char *zPattern, const char *zStr){
  int i = 0;
  int j = 0;

  while( zPattern[i] ){
    char p = zPattern[i];

    if( p=='*' || p=='%' ){
      do {
        if( testGlobMatch(&zPattern[i+1], &zStr[j]) ) return 1;
      }while( zStr[j++] );
      return 0;
    }

    if( zStr[j]==0 || (p!='?' && p!=zStr[j]) ){
      /* Match failed. */
      return 0;
    }

    j++;
    i++;
  }

  return (zPattern[i]==0 && zStr[j]==0);
}