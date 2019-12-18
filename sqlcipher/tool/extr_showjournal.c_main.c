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
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ db ; 
 scalar_t__ decode_journal_header (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int fileSize ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fseek (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (scalar_t__) ; 
 int pageSize ; 
 int /*<<< orphan*/  print_page (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sectorSize ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv){
  int nPage, cnt;
  int iOfst;
  if( argc!=2 ){
    fprintf(stderr,"Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }
  db = fopen(argv[1], "rb");
  if( db==0 ){
    fprintf(stderr,"%s: can't open %s\n", argv[0], argv[1]);
    exit(1);
  }
  fseek(db, 0, SEEK_END);
  fileSize = ftell(db);
  printf("journal file size: %d bytes\n", fileSize);
  fseek(db, 0, SEEK_SET);
  iOfst = 0;
  while( iOfst<fileSize ){
    cnt = nPage = (int)decode_journal_header(iOfst);
    if( cnt==0 ){
      cnt = (fileSize - sectorSize)/(pageSize+8);
    }
    iOfst += sectorSize;
    while( cnt && iOfst<fileSize ){
      print_page(iOfst);
      iOfst += pageSize+8;
    }
    iOfst = (iOfst/sectorSize + 1)*sectorSize;
  }
  fclose(db);
  return 0;
}