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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (void*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 void* sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void readFile(const char *zFilename, int *pSz, void **ppBuf){
  FILE *f;
  sqlite3_int64 sz;
  void *pBuf;
  f = fopen(zFilename, "rb");
  if( f==0 ){
    fprintf(stderr, "cannot open \"%s\" for reading\n", zFilename);
    exit(1);
  }
  fseek(f, 0, SEEK_END);
  sz = ftell(f);
  rewind(f);
  pBuf = sqlite3_malloc64( sz ? sz : 1 );
  if( pBuf==0 ){
    fprintf(stderr, "cannot allocate %d to hold content of \"%s\"\n",
            (int)sz, zFilename);
    exit(1);
  }
  if( sz>0 ){
    if( fread(pBuf, (size_t)sz, 1, f)!=1 ){
      fprintf(stderr, "cannot read all %d bytes of \"%s\"\n",
              (int)sz, zFilename);
      exit(1);
    }
    fclose(f);
  }
  *pSz = (int)sz;
  *ppBuf = pBuf;
}