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
struct TYPE_3__ {struct TYPE_3__* aiException; } ;
typedef  TYPE_1__ unicode_tokenizer ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 

__attribute__((used)) static int unicodeDestroy(sqlite3_tokenizer *pTokenizer){
  if( pTokenizer ){
    unicode_tokenizer *p = (unicode_tokenizer *)pTokenizer;
    sqlite3_free(p->aiException);
    sqlite3_free(p);
  }
  return SQLITE_OK;
}