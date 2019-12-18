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
 unsigned int CR_OK ; 
 unsigned int WSEOL_OK ; 
 int /*<<< orphan*/  checkSpacing (char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int main(int argc, char **argv){
  int i;
  unsigned flags = WSEOL_OK;
  for(i=1; i<argc; i++){
    const char *z = argv[i];
    if( z[0]=='-' ){
      while( z[0]=='-' ) z++;
      if( strcmp(z,"crok")==0 ){
        flags |= CR_OK;
      }else if( strcmp(z, "wseol")==0 ){
        flags &= ~WSEOL_OK;
      }else if( strcmp(z, "help")==0 ){
        printf("Usage: %s [options] FILE ...\n", argv[0]);
        printf("  --crok      Do not report on carriage-returns\n");
        printf("  --wseol     Complain about whitespace at end-of-line\n");
        printf("  --help      This message\n");
      }else{
        printf("unknown command-line option: [%s]\n", argv[i]);
        printf("use --help for additional information\n");
      }
    }else{
      checkSpacing(argv[i], flags);
    }
  }
  return 0;
}