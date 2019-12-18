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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void unrecognizedArguments(
  const char *argv0,
  int nArg,
  char **azArg
){
  int i;
  fprintf(stderr,"%s: unrecognized arguments:", argv0);
  for(i=0; i<nArg; i++){
    fprintf(stderr," %s", azArg[i]);
  }
  fprintf(stderr,"\n");
  exit(1);
}