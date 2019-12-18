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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fileSize (char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (unsigned char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 
 unsigned char* sqlite3_malloc64 (scalar_t__) ; 

__attribute__((used)) static unsigned char *readFile(const char *zName, sqlite3_int64 *pnByte){
  FILE *in;               /* FILE from which to read content of zName */
  sqlite3_int64 nIn;      /* Size of zName in bytes */
  size_t nRead;           /* Number of bytes actually read */
  unsigned char *pBuf;    /* Content read from disk */

  nIn = fileSize(zName);
  if( nIn<0 ) return 0;
  in = fopen(zName, "rb");
  if( in==0 ) return 0;
  pBuf = sqlite3_malloc64( nIn );
  if( pBuf==0 ) return 0;
  nRead = fread(pBuf, (size_t)nIn, 1, in);
  fclose(in);
  if( nRead!=1 ){
    sqlite3_free(pBuf);
    return 0;
  }
  if( pnByte ) *pnByte = nIn;
  return pBuf;
}