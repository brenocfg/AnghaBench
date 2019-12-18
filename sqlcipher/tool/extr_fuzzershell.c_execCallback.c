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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int execCallback(void *NotUsed, int argc, char **argv, char **colv){
  int i;
  static unsigned cnt = 0;
  printf("ROW #%u:\n", ++cnt);
  if( argv ){
    for(i=0; i<argc; i++){
      printf(" %s=", colv[i]);
      if( argv[i] ){
        printf("[%s]\n", argv[i]);
      }else{
        printf("NULL\n");
      }
    }
  }
  fflush(stdout);
  return 0;
}