#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* aiException; int nException; } ;
typedef  TYPE_1__ unicode_tokenizer ;

/* Variables and functions */
 int /*<<< orphan*/  READ_UTF8 (unsigned char const*,unsigned char const*,unsigned int) ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3FtsUnicodeIsalnum (int) ; 
 scalar_t__ sqlite3FtsUnicodeIsdiacritic (int) ; 
 int* sqlite3_realloc64 (int*,int) ; 

__attribute__((used)) static int unicodeAddExceptions(
  unicode_tokenizer *p,           /* Tokenizer to add exceptions to */
  int bAlnum,                     /* Replace Isalnum() return value with this */
  const char *zIn,                /* Array of characters to make exceptions */
  int nIn                         /* Length of z in bytes */
){
  const unsigned char *z = (const unsigned char *)zIn;
  const unsigned char *zTerm = &z[nIn];
  unsigned int iCode;
  int nEntry = 0;

  assert( bAlnum==0 || bAlnum==1 );

  while( z<zTerm ){
    READ_UTF8(z, zTerm, iCode);
    assert( (sqlite3FtsUnicodeIsalnum((int)iCode) & 0xFFFFFFFE)==0 );
    if( sqlite3FtsUnicodeIsalnum((int)iCode)!=bAlnum 
     && sqlite3FtsUnicodeIsdiacritic((int)iCode)==0 
    ){
      nEntry++;
    }
  }

  if( nEntry ){
    int *aNew;                    /* New aiException[] array */
    int nNew;                     /* Number of valid entries in array aNew[] */

    aNew = sqlite3_realloc64(p->aiException,(p->nException+nEntry)*sizeof(int));
    if( aNew==0 ) return SQLITE_NOMEM;
    nNew = p->nException;

    z = (const unsigned char *)zIn;
    while( z<zTerm ){
      READ_UTF8(z, zTerm, iCode);
      if( sqlite3FtsUnicodeIsalnum((int)iCode)!=bAlnum 
       && sqlite3FtsUnicodeIsdiacritic((int)iCode)==0
      ){
        int i, j;
        for(i=0; i<nNew && aNew[i]<(int)iCode; i++);
        for(j=nNew; j>i; j--) aNew[j] = aNew[j-1];
        aNew[i] = (int)iCode;
        nNew++;
      }
    }
    p->aiException = aNew;
    p->nException = nNew;
  }

  return SQLITE_OK;
}