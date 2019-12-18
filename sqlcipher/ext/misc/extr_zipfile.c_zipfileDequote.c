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
 scalar_t__ ALWAYS (char) ; 

__attribute__((used)) static void zipfileDequote(char *zIn){
  char q = zIn[0];
  if( q=='"' || q=='\'' || q=='`' || q=='[' ){
    int iIn = 1;
    int iOut = 0;
    if( q=='[' ) q = ']';
    while( ALWAYS(zIn[iIn]) ){
      char c = zIn[iIn++];
      if( c==q && zIn[iIn++]!=q ) break;
      zIn[iOut++] = c;
    }
    zIn[iOut] = '\0';
  }
}