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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int fwrite (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void fuzzWriteFile(const char *zFilename, void *pBuf, int nBuf){
  FILE *f;
  f = fopen(zFilename, "wb");
  if( f==0 ){
    fprintf(stderr, "cannot open \"%s\" for writing\n", zFilename);
    exit(1);
  }
  if( fwrite(pBuf, nBuf, 1, f)!=1 ){
    fprintf(stderr, "cannot write to \"%s\"\n", zFilename);
    exit(1);
  }
  fclose(f);
}