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
 int all_stop ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int check_callback(void *pid, int argc, char **argv, char **notUsed2){
  int id = (int)pid;
  if( strcmp(argv[0],"ok") ){
    all_stop = 1;
    fprintf(stderr,"%d: %s\n", id, argv[0]);
  }else{
    /* fprintf(stderr,"%d: OK\n", id); */
  }
  return 0;
}