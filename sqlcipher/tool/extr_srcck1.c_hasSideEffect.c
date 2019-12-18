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
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int hasSideEffect(const char *z, unsigned int n){
  unsigned int i;
  for(i=0; i<n; i++){
    if( z[i]=='/' && strncmp(&z[i], "/*side-effects-ok*/", 19)==0 ) return 0;
    if( z[i]=='=' && i>0 && z[i-1]!='=' && z[i-1]!='>'
           && z[i-1]!='<' && z[i-1]!='!' && z[i+1]!='=' ) return 1;
    if( z[i]=='+' && z[i+1]=='+' ) return 1;
    if( z[i]=='-' && z[i+1]=='-' ) return 1;
  }
  return 0;
}