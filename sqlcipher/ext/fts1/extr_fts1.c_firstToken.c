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
 int TOKEN_EOF ; 
 int TOKEN_SPACE ; 
 int /*<<< orphan*/  dequoteString (char*) ; 
 int getToken (char*,int*) ; 

__attribute__((used)) static char *firstToken(char *zIn, char **pzTail){
  int n, ttype;
  while(1){
    n = getToken(zIn, &ttype);
    if( ttype==TOKEN_SPACE ){
      zIn += n;
    }else if( ttype==TOKEN_EOF ){
      *pzTail = zIn;
      return 0;
    }else{
      zIn[n] = 0;
      *pzTail = &zIn[1];
      dequoteString(zIn);
      return zIn;
    }
  }
  /*NOTREACHED*/
}