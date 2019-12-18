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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (char*,int,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 char* sqlite3_malloc64 (long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void readFile(const char *zName, void **ppData, int *pnData){
  FILE *in = fopen(zName, "rb");
  long nIn;
  size_t nRead;
  char *pBuf;
  *ppData = 0;
  *pnData = 0;
  if( in==0 ){
    fprintf(stderr, "Cannot open \"%s\" for reading\n", zName);
    exit(1);
  }
  fseek(in, 0, SEEK_END);
  nIn = ftell(in);
  rewind(in);
  pBuf = sqlite3_malloc64( nIn+1 );
  if( pBuf==0 ){
    fprintf(stderr, "Failed to malloc %lld bytes\n", (sqlite3_int64)(nIn+1));
    exit(1);
  }
  nRead = fread(pBuf, 1, nIn, in);
  fclose(in);
  if( nRead!=(size_t)nIn ){
    fprintf(stderr, "Read only %d of %d bytes from %s\n", (int)nRead, (int)nIn,
                    zName);
    exit(1);
  }
  pBuf[nIn] = 0;
  *pnData = nIn;
  *ppData = pBuf;
}