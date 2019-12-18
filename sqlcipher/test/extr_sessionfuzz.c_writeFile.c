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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fwrite (void const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void writeFile(const char *zFilename, const void *pData, int nData){
  FILE *out;
  int n;
  out = fopen(zFilename, "wb");
  if( out==0 ){
    fprintf(stderr, "cannot open \"%s\" for writing\n", zFilename);
    exit(1);
  }
  n = (int)fwrite(pData, 1, nData, out);
  fclose(out);
  if( n!=nData ){
    fprintf(stderr, "only wrote %d of %d bytes to \"%s\"\n",n,nData,zFilename);
    exit(1);
  }
}