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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lemonStrlen (char*) ; 
 int /*<<< orphan*/  lemon_strcpy (char*,char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 char* outputDir ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void handle_d_option(char *z){
  outputDir = (char *) malloc( lemonStrlen(z)+1 );
  if( outputDir==0 ){
    fprintf(stderr,"out of memory\n");
    exit(1);
  }
  lemon_strcpy(outputDir, z);
}