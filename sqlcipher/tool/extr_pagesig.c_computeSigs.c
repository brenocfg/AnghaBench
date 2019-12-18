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
typedef  int /*<<< orphan*/  aBuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (unsigned char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vlogSignature (unsigned char*,unsigned int,unsigned char*) ; 

__attribute__((used)) static void computeSigs(const char *zFilename){
  FILE *in = fopen(zFilename, "rb");
  unsigned pgsz;
  size_t got;
  unsigned n;
  unsigned char aBuf[50];
  unsigned char aPage[65536];

  if( in==0 ){
    fprintf(stderr, "cannot open \"%s\"\n", zFilename);
    return;
  }
  got = fread(aBuf, 1, sizeof(aBuf), in);
  if( got!=sizeof(aBuf) ){
    goto endComputeSigs;
  }
  pgsz = aBuf[16]*256 + aBuf[17];
  if( pgsz==1 ) pgsz = 65536;
  if( (pgsz & (pgsz-1))!=0 ){
    fprintf(stderr, "invalid page size: %02x%02x\n", aBuf[16], aBuf[17]);
    goto endComputeSigs;
  }
  rewind(in);
  for(n=1; (got=fread(aPage, 1, pgsz, in))==pgsz; n++){
    vlogSignature(aPage, pgsz, aBuf);
    printf("%4d: %s\n", n, aBuf);
  }

endComputeSigs:
  fclose(in);
}