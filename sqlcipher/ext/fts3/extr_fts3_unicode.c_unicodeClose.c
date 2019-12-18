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
struct TYPE_3__ {struct TYPE_3__* zToken; } ;
typedef  TYPE_1__ unicode_cursor ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int unicodeClose(sqlite3_tokenizer_cursor *pCursor){
  unicode_cursor *pCsr = (unicode_cursor *) pCursor;
  sqlite3_free(pCsr->zToken);
  sqlite3_free(pCsr);
  return SQLITE_OK;
}