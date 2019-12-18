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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* getContent (int /*<<< orphan*/ ,int) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_ckpt_info (unsigned char*) ; 
 int /*<<< orphan*/  print_index_hdr (unsigned char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv){
  unsigned char *aData;
  if( argc<2 ){
    fprintf(stderr,"Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
  fd = open(argv[1], O_RDONLY);
  if( fd<0 ){
    fprintf(stderr,"%s: can't open %s\n", argv[0], argv[1]);
    exit(1);
  }
  aData = getContent(0, 136);
  print_index_hdr(aData, 0);
  print_index_hdr(aData, 1);
  print_ckpt_info(aData);
  free(aData);
  close(fd);
  return 0;
}