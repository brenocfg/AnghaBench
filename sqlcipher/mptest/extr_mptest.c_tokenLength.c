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
 scalar_t__ ISSPACE (char const) ; 

__attribute__((used)) static int tokenLength(const char *z, int *pnLine){
  int n = 0;
  if( ISSPACE(z[0]) || (z[0]=='/' && z[1]=='*') ){
    int inC = 0;
    int c;
    if( z[0]=='/' ){
      inC = 1;
      n = 2;
    }
    while( (c = z[n++])!=0 ){
      if( c=='\n' ) (*pnLine)++;
      if( ISSPACE(c) ) continue;
      if( inC && c=='*' && z[n]=='/' ){
        n++;
        inC = 0;
      }else if( !inC && c=='/' && z[n]=='*' ){
        n++;
        inC = 1;
      }else if( !inC ){
        break;
      }
    }
    n--;
  }else if( z[0]=='-' && z[1]=='-' ){
    for(n=2; z[n] && z[n]!='\n'; n++){}
    if( z[n] ){ (*pnLine)++; n++; }
  }else if( z[0]=='"' || z[0]=='\'' ){
    int delim = z[0];
    for(n=1; z[n]; n++){
      if( z[n]=='\n' ) (*pnLine)++;
      if( z[n]==delim ){
        n++;
        if( z[n+1]!=delim ) break;
      }
    }
  }else{
    int c;
    for(n=1; (c = z[n])!=0 && !ISSPACE(c) && c!='"' && c!='\'' && c!=';'; n++){}
  }
  return n;
}