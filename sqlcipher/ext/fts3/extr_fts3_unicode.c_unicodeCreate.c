#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int eRemoveDiacritic; } ;
typedef  TYPE_1__ unicode_tokenizer ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 scalar_t__ strlen (char const*) ; 
 int unicodeAddExceptions (TYPE_1__*,int,char const*,int) ; 
 int /*<<< orphan*/  unicodeDestroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unicodeCreate(
  int nArg,                       /* Size of array argv[] */
  const char * const *azArg,      /* Tokenizer creation arguments */
  sqlite3_tokenizer **pp          /* OUT: New tokenizer handle */
){
  unicode_tokenizer *pNew;        /* New tokenizer object */
  int i;
  int rc = SQLITE_OK;

  pNew = (unicode_tokenizer *) sqlite3_malloc(sizeof(unicode_tokenizer));
  if( pNew==NULL ) return SQLITE_NOMEM;
  memset(pNew, 0, sizeof(unicode_tokenizer));
  pNew->eRemoveDiacritic = 1;

  for(i=0; rc==SQLITE_OK && i<nArg; i++){
    const char *z = azArg[i];
    int n = (int)strlen(z);

    if( n==19 && memcmp("remove_diacritics=1", z, 19)==0 ){
      pNew->eRemoveDiacritic = 1;
    }
    else if( n==19 && memcmp("remove_diacritics=0", z, 19)==0 ){
      pNew->eRemoveDiacritic = 0;
    }
    else if( n==19 && memcmp("remove_diacritics=2", z, 19)==0 ){
      pNew->eRemoveDiacritic = 2;
    }
    else if( n>=11 && memcmp("tokenchars=", z, 11)==0 ){
      rc = unicodeAddExceptions(pNew, 1, &z[11], n-11);
    }
    else if( n>=11 && memcmp("separators=", z, 11)==0 ){
      rc = unicodeAddExceptions(pNew, 0, &z[11], n-11);
    }
    else{
      /* Unrecognized argument */
      rc  = SQLITE_ERROR;
    }
  }

  if( rc!=SQLITE_OK ){
    unicodeDestroy((sqlite3_tokenizer *)pNew);
    pNew = 0;
  }
  *pp = (sqlite3_tokenizer *)pNew;
  return rc;
}