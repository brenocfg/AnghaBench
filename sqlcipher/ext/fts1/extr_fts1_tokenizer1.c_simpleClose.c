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
typedef  int /*<<< orphan*/  sqlite3_tokenizer_cursor ;
struct TYPE_3__ {struct TYPE_3__* pToken; } ;
typedef  TYPE_1__ simple_tokenizer_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static int simpleClose(sqlite3_tokenizer_cursor *pCursor){
  simple_tokenizer_cursor *c = (simple_tokenizer_cursor *) pCursor;
  free(c->pToken);
  free(c);
  return SQLITE_OK;
}