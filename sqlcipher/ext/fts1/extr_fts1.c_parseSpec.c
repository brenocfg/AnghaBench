#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* zDb; char* zName; size_t nColumn; char** azColumn; char** azContentColumn; int /*<<< orphan*/  azTokenizer; } ;
typedef  TYPE_1__ TableSpec ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clearTableSpec (TYPE_1__*) ; 
 char* firstToken (char*,char**) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_isalnum (char) ; 
 char* sqlite3_mprintf (char*,int,char*) ; 
 scalar_t__ startsWith (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const* const) ; 
 scalar_t__ strlen (char const* const) ; 
 int /*<<< orphan*/  tokenListToIdList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tokenizeString (char const*,int*) ; 

__attribute__((used)) static int parseSpec(TableSpec *pSpec, int argc, const char *const*argv,
                     char**pzErr){
  int i, n;
  char *z, *zDummy;
  char **azArg;
  const char *zTokenizer = 0;    /* argv[] entry describing the tokenizer */

  assert( argc>=3 );
  /* Current interface:
  ** argv[0] - module name
  ** argv[1] - database name
  ** argv[2] - table name
  ** argv[3..] - columns, optionally followed by tokenizer specification
  **             and snippet delimiters specification.
  */

  /* Make a copy of the complete argv[][] array in a single allocation.
  ** The argv[][] array is read-only and transient.  We can write to the
  ** copy in order to modify things and the copy is persistent.
  */
  memset(pSpec, 0, sizeof(*pSpec));
  for(i=n=0; i<argc; i++){
    n += strlen(argv[i]) + 1;
  }
  azArg = malloc( sizeof(char*)*argc + n );
  if( azArg==0 ){
    return SQLITE_NOMEM;
  }
  z = (char*)&azArg[argc];
  for(i=0; i<argc; i++){
    azArg[i] = z;
    strcpy(z, argv[i]);
    z += strlen(z)+1;
  }

  /* Identify the column names and the tokenizer and delimiter arguments
  ** in the argv[][] array.
  */
  pSpec->zDb = azArg[1];
  pSpec->zName = azArg[2];
  pSpec->nColumn = 0;
  pSpec->azColumn = azArg;
  zTokenizer = "tokenize simple";
  for(i=3; i<argc; ++i){
    if( startsWith(azArg[i],"tokenize") ){
      zTokenizer = azArg[i];
    }else{
      z = azArg[pSpec->nColumn] = firstToken(azArg[i], &zDummy);
      pSpec->nColumn++;
    }
  }
  if( pSpec->nColumn==0 ){
    azArg[0] = "content";
    pSpec->nColumn = 1;
  }

  /*
  ** Construct the list of content column names.
  **
  ** Each content column name will be of the form cNNAAAA
  ** where NN is the column number and AAAA is the sanitized
  ** column name.  "sanitized" means that special characters are
  ** converted to "_".  The cNN prefix guarantees that all column
  ** names are unique.
  **
  ** The AAAA suffix is not strictly necessary.  It is included
  ** for the convenience of people who might examine the generated
  ** %_content table and wonder what the columns are used for.
  */
  pSpec->azContentColumn = malloc( pSpec->nColumn * sizeof(char *) );
  if( pSpec->azContentColumn==0 ){
    clearTableSpec(pSpec);
    return SQLITE_NOMEM;
  }
  for(i=0; i<pSpec->nColumn; i++){
    char *p;
    pSpec->azContentColumn[i] = sqlite3_mprintf("c%d%s", i, azArg[i]);
    for (p = pSpec->azContentColumn[i]; *p ; ++p) {
      if( !safe_isalnum(*p) ) *p = '_';
    }
  }

  /*
  ** Parse the tokenizer specification string.
  */
  pSpec->azTokenizer = tokenizeString(zTokenizer, &n);
  tokenListToIdList(pSpec->azTokenizer);

  return SQLITE_OK;
}