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
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fatalError (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fileSize (char const*) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  fsync (int /*<<< orphan*/ ) ; 
 size_t fwrite (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 
 unsigned char* sqlite3_malloc64 (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,unsigned char*) ; 

__attribute__((used)) static void updateFile(const char *zName, sqlite3_int64 *pnByte, int doFsync){
  FILE *out;              /* FILE from which to read content of zName */
  sqlite3_int64 sz;       /* Size of zName in bytes */
  size_t nWritten;        /* Number of bytes actually read */
  unsigned char *pBuf;    /* Content to store on disk */
  const char *zMode = "wb";   /* Mode for fopen() */

  sz = fileSize(zName);
  if( sz<0 ){
    fatalError("No such file: \"%s\"", zName);
  }
  *pnByte = sz;
  if( sz==0 ) return;
  pBuf = sqlite3_malloc64( sz );
  if( pBuf==0 ){
    fatalError("Cannot allocate %lld bytes\n", sz);
  }
  sqlite3_randomness((int)sz, pBuf); 
#if defined(_WIN32)
  if( doFsync ) zMode = "wbc";
#endif
  out = fopen(zName, zMode);
  if( out==0 ){
    fatalError("Cannot open \"%s\" for writing\n", zName);
  }
  nWritten = fwrite(pBuf, 1, (size_t)sz, out);
  if( doFsync ){
#if defined(_WIN32)
    fflush(out);
#else
    fsync(fileno(out));
#endif
  }
  fclose(out);
  if( nWritten!=(size_t)sz ){
    fatalError("Wrote only %d of %d bytes to \"%s\"\n",
               (int)nWritten, (int)sz, zName);
  }
  sqlite3_free(pBuf);
}