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
 char** azExtra ; 
 int nExtra ; 
 scalar_t__ strcmp (char const*,char const*) ; 

const char *findOption(const char *zName, int hasArg, const char *zDefault){
  int i;
  const char *zResult = zDefault;
  for(i=0; i<nExtra; i++){
    const char *z = azExtra[i];
    while( z[0]=='-' ) z++;
    if( strcmp(z, zName)==0 ){
      int j = 1;
      if( hasArg==0 || i==nExtra-1 ) j = 0;
      zResult = azExtra[i+j];
      while( i+j<nExtra ){
        azExtra[i] = azExtra[i+j+1];
        i++;
      }
      break;
    }
  }
  return zResult;       
}