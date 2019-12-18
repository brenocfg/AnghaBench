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
typedef  unsigned int sqlite3_uint64 ;

/* Variables and functions */
 unsigned int MX_FILE_SZ ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ eVerbosity ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 unsigned char hexToInt (unsigned char) ; 
 scalar_t__ isOffset (unsigned char const*,int,unsigned int*,unsigned int*) ; 
 scalar_t__ isxdigit (unsigned char) ; 
 scalar_t__ memcmp (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 
 unsigned char* sqlite3_malloc64 (unsigned int) ; 
 unsigned char* sqlite3_realloc64 (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int decodeDatabase(
  const unsigned char *zIn,      /* Input text to be decoded */
  int nIn,                       /* Bytes of input text */
  unsigned char **paDecode,      /* OUT: decoded database file */
  int *pnDecode                  /* OUT: Size of decoded database */
){
  unsigned char *a;              /* Database under construction */
  int mx = 0;                    /* Current size of the database */
  sqlite3_uint64 nAlloc = 4096;  /* Space allocated in a[] */
  unsigned int i;                /* Next byte of zIn[] to read */
  unsigned int j;                /* Temporary integer */
  unsigned int k;                /* half-byte cursor index for output */
  unsigned int n;                /* Number of bytes of input */
  unsigned char b = 0;
  if( nIn<4 ) return -1;
  n = (unsigned int)nIn;
  a = sqlite3_malloc64( nAlloc );
  if( a==0 ){
    fprintf(stderr, "Out of memory!\n");
    exit(1);
  }
  memset(a, 0, (size_t)nAlloc);
  for(i=k=0; i<n; i++){
    unsigned char c = (unsigned char)zIn[i];
    if( isxdigit(c) ){
      k++;
      if( k & 1 ){
        b = hexToInt(c)*16;
      }else{
        b += hexToInt(c);
        j = k/2 - 1;
        if( j>=nAlloc ){
          sqlite3_uint64 newSize;
          if( nAlloc==MX_FILE_SZ || j>=MX_FILE_SZ ){
            if( eVerbosity ){
              fprintf(stderr, "Input database too big: max %d bytes\n",
                      MX_FILE_SZ);
            }
            sqlite3_free(a);
            return -1;
          }
          newSize = nAlloc*2;
          if( newSize<=j ){
            newSize = (j+4096)&~4095;
          }
          if( newSize>MX_FILE_SZ ){
            if( j>=MX_FILE_SZ ){
              sqlite3_free(a);
              return -1;
            }
            newSize = MX_FILE_SZ;
          }
          a = sqlite3_realloc64( a, newSize );
          if( a==0 ){
            fprintf(stderr, "Out of memory!\n");
            exit(1);
          }
          assert( newSize > nAlloc );
          memset(a+nAlloc, 0, (size_t)(newSize - nAlloc));
          nAlloc = newSize;
        }
        if( j>=(unsigned)mx ){
          mx = (j + 4095)&~4095;
          if( mx>MX_FILE_SZ ) mx = MX_FILE_SZ;
        }
        assert( j<nAlloc );
        a[j] = b;
      }
    }else if( zIn[i]=='[' && i<n-3 && isOffset(zIn+i, nIn-i, &k, &i) ){
      continue;
   }else if( zIn[i]=='\n' && i<n-4 && memcmp(zIn+i,"\n--\n",4)==0 ){
      i += 4;
      break;
    }
  }
  *pnDecode = mx;
  *paDecode = a;
  return i;
}