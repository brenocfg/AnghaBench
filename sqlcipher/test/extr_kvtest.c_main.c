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
 int exportMain (int,char**) ; 
 int initMain (int,char**) ; 
 int runMain (int,char**) ; 
 int /*<<< orphan*/  showHelp () ; 
 int statMain (int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char **argv){
  if( argc<3 ) showHelp();
  if( strcmp(argv[1],"init")==0 ){
    return initMain(argc, argv);
  }
  if( strcmp(argv[1],"export")==0 ){
    return exportMain(argc, argv);
  }
  if( strcmp(argv[1],"run")==0 ){
    return runMain(argc, argv);
  }
  if( strcmp(argv[1],"stat")==0 ){
    return statMain(argc, argv);
  }
  showHelp();
  return 0;
}