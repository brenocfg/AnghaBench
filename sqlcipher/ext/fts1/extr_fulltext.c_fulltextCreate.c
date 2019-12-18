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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fulltextConnect (int /*<<< orphan*/ *,void*,int,char const* const*,int /*<<< orphan*/ **,char**) ; 
 int sql_exec (int /*<<< orphan*/ *,char const* const,char*) ; 

__attribute__((used)) static int fulltextCreate(
  sqlite3 *db,
  void *pAux,
  int argc,
  const char * const *argv,
  sqlite3_vtab **ppVTab,
  char **pzErr
){
  int rc;
  assert( argc>=3 );

  /* The %_content table holds the text of each full-text item, with
  ** the rowid used as the docid.
  **
  ** The %_term table maps each term to a document list blob
  ** containing elements sorted by ascending docid, each element
  ** encoded as:
  **
  **   docid varint-encoded
  **   token count varint-encoded
  **   "count" token elements (poslist):
  **     position varint-encoded as delta from previous position
  **     start offset varint-encoded as delta from previous start offset
  **     end offset varint-encoded as delta from start offset
  **
  ** Additionally, doclist blobs can be chunked into multiple rows,
  ** using "first" to order the blobs.  "first" is simply the first
  ** docid in the blob.
  */
  /*
  ** NOTE(shess) That last sentence is incorrect in the face of
  ** deletion, which can leave a doclist that doesn't contain the
  ** first from that row.  I _believe_ this does not matter to the
  ** operation of the system, but it might be reasonable to update
  ** appropriately in case this assumption becomes more important.
  */
  rc = sql_exec(db, argv[2],
    "create table %_content(content text);"
    "create table %_term(term text, first integer, doclist blob);"
    "create index %_index on %_term(term, first)");
  if( rc!=SQLITE_OK ) return rc;

  return fulltextConnect(db, pAux, argc, argv, ppVTab, pzErr);
}