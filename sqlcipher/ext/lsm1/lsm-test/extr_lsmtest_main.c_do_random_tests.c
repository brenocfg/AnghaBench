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
 int atoi (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  testPrintError (char*) ; 
 int testPrngValue (int) ; 

int do_random_tests(int nArg, char **azArg){
  int i;
  int nRand;
  if( nArg==0 ){
    nRand = 10;
  }else if( nArg==1 ){
    nRand = atoi(azArg[0]);
  }else{
    testPrintError("Usage: random ?N?\n");
    return -1;
  }
  for(i=0; i<nRand; i++){
    printf("0x%x\n", testPrngValue(i));
  }
  return 0;
}