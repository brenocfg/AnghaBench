#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  pCursor ;
struct TYPE_6__ {int /*<<< orphan*/  nSnippet; int /*<<< orphan*/  zSnippet; } ;
struct TYPE_7__ {TYPE_1__ snippet; } ;
typedef  TYPE_2__ fulltext_cursor ;

/* Variables and functions */
 scalar_t__ SQLITE_BLOB ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  memcpy (TYPE_2__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snippetAllOffsets (TYPE_2__*) ; 
 int /*<<< orphan*/  snippetText (TYPE_2__*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snippetFunc(
  sqlite3_context *pContext,
  int argc,
  sqlite3_value **argv
){
  fulltext_cursor *pCursor;
  if( argc<1 ) return;
  if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
      sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
    sqlite3_result_error(pContext, "illegal first argument to html_snippet",-1);
  }else{
    const char *zStart = "<b>";
    const char *zEnd = "</b>";
    const char *zEllipsis = "<b>...</b>";
    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
    if( argc>=2 ){
      zStart = (const char*)sqlite3_value_text(argv[1]);
      if( argc>=3 ){
        zEnd = (const char*)sqlite3_value_text(argv[2]);
        if( argc>=4 ){
          zEllipsis = (const char*)sqlite3_value_text(argv[3]);
        }
      }
    }
    snippetAllOffsets(pCursor);
    snippetText(pCursor, zStart, zEnd, zEllipsis);
    sqlite3_result_text(pContext, pCursor->snippet.zSnippet,
                        pCursor->snippet.nSnippet, SQLITE_STATIC);
  }
}