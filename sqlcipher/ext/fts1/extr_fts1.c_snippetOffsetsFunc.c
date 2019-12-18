#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  pCursor ;
struct TYPE_6__ {int /*<<< orphan*/  nOffset; int /*<<< orphan*/  zOffset; } ;
struct TYPE_5__ {TYPE_2__ snippet; } ;
typedef  TYPE_1__ fulltext_cursor ;

/* Variables and functions */
 scalar_t__ SQLITE_BLOB ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  memcpy (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snippetAllOffsets (TYPE_1__*) ; 
 int /*<<< orphan*/  snippetOffsetText (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snippetOffsetsFunc(
  sqlite3_context *pContext,
  int argc,
  sqlite3_value **argv
){
  fulltext_cursor *pCursor;
  if( argc<1 ) return;
  if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
      sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
    sqlite3_result_error(pContext, "illegal first argument to offsets",-1);
  }else{
    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
    snippetAllOffsets(pCursor);
    snippetOffsetText(&pCursor->snippet);
    sqlite3_result_text(pContext,
                        pCursor->snippet.zOffset, pCursor->snippet.nOffset,
                        SQLITE_STATIC);
  }
}