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
 scalar_t__ ISSPACE (char) ; 
 char** azDefine ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int lemonStrlen (char*) ; 
 int nDefine ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void preprocess_input(char *z){
  int i, j, k, n;
  int exclude = 0;
  int start = 0;
  int lineno = 1;
  int start_lineno = 1;
  for(i=0; z[i]; i++){
    if( z[i]=='\n' ) lineno++;
    if( z[i]!='%' || (i>0 && z[i-1]!='\n') ) continue;
    if( strncmp(&z[i],"%endif",6)==0 && ISSPACE(z[i+6]) ){
      if( exclude ){
        exclude--;
        if( exclude==0 ){
          for(j=start; j<i; j++) if( z[j]!='\n' ) z[j] = ' ';
        }
      }
      for(j=i; z[j] && z[j]!='\n'; j++) z[j] = ' ';
    }else if( (strncmp(&z[i],"%ifdef",6)==0 && ISSPACE(z[i+6]))
          || (strncmp(&z[i],"%ifndef",7)==0 && ISSPACE(z[i+7])) ){
      if( exclude ){
        exclude++;
      }else{
        for(j=i+7; ISSPACE(z[j]); j++){}
        for(n=0; z[j+n] && !ISSPACE(z[j+n]); n++){}
        exclude = 1;
        for(k=0; k<nDefine; k++){
          if( strncmp(azDefine[k],&z[j],n)==0 && lemonStrlen(azDefine[k])==n ){
            exclude = 0;
            break;
          }
        }
        if( z[i+3]=='n' ) exclude = !exclude;
        if( exclude ){
          start = i;
          start_lineno = lineno;
        }
      }
      for(j=i; z[j] && z[j]!='\n'; j++) z[j] = ' ';
    }
  }
  if( exclude ){
    fprintf(stderr,"unterminated %%ifdef starting on line %d\n", start_lineno);
    exit(1);
  }
}