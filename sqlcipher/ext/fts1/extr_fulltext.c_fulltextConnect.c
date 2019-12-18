#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int (* xCreate ) (int,char const**,TYPE_3__**) ;} ;
typedef  TYPE_1__ sqlite3_tokenizer_module ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {int /*<<< orphan*/  base; int /*<<< orphan*/  pFulltextStatements; TYPE_3__* pTokenizer; int /*<<< orphan*/  zName; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ fulltext_vtab ;
struct TYPE_7__ {TYPE_1__* pModule; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_simple_tokenizer_module (TYPE_1__**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char const* const,char*) ; 
 int /*<<< orphan*/  string_dup (char const* const) ; 
 int stub1 (int,char const**,TYPE_3__**) ; 

__attribute__((used)) static int fulltextConnect(
  sqlite3 *db,
  void *pAux,
  int argc,
  const char * const *argv,
  sqlite3_vtab **ppVTab,
  char **pzErr
){
  int rc;
  fulltext_vtab *v;
  sqlite3_tokenizer_module *m = NULL;

  assert( argc>=3 );
  v = (fulltext_vtab *) malloc(sizeof(fulltext_vtab));
  /* sqlite will initialize v->base */
  v->db = db;
  v->zName = string_dup(argv[2]);
  v->pTokenizer = NULL;

  if( argc==3 ){
    get_simple_tokenizer_module(&m);
  } else {
    /* TODO(shess) For now, add new tokenizers as else if clauses. */
    if( !strcmp(argv[3], "simple") ){
      get_simple_tokenizer_module(&m);
    } else {
      assert( "unrecognized tokenizer"==NULL );
    }
  }

  /* TODO(shess) Since tokenization impacts the index, the parameters
  ** to the tokenizer need to be identical when a persistent virtual
  ** table is re-created.  One solution would be a meta-table to track
  ** such information in the database.  Then we could verify that the
  ** information is identical on subsequent creates.
  */
  /* TODO(shess) Why isn't argv already (const char **)? */
  rc = m->xCreate(argc-3, (const char **) (argv+3), &v->pTokenizer);
  if( rc!=SQLITE_OK ) return rc;
  v->pTokenizer->pModule = m;

  /* TODO: verify the existence of backing tables foo_content, foo_term */

  rc = sqlite3_declare_vtab(db, "create table x(content text)");
  if( rc!=SQLITE_OK ) return rc;

  memset(v->pFulltextStatements, 0, sizeof(v->pFulltextStatements));

  *ppVTab = &v->base;
  return SQLITE_OK;
}