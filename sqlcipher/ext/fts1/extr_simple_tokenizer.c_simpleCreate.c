#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zDelim ;
typedef  int /*<<< orphan*/  sqlite3_tokenizer ;
struct TYPE_2__ {int /*<<< orphan*/  base; void* zDelim; } ;
typedef  TYPE_1__ simple_tokenizer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 scalar_t__ malloc (int) ; 
 void* string_dup (char const*) ; 

__attribute__((used)) static int simpleCreate(
  int argc, const char **argv,
  sqlite3_tokenizer **ppTokenizer
){
  simple_tokenizer *t;

  t = (simple_tokenizer *) malloc(sizeof(simple_tokenizer));
  /* TODO(shess) Delimiters need to remain the same from run to run,
  ** else we need to reindex.  One solution would be a meta-table to
  ** track such information in the database, then we'd only want this
  ** information on the initial create.
  */
  if( argc>1 ){
    t->zDelim = string_dup(argv[1]);
  } else {
    /* Build a string excluding alphanumeric ASCII characters */
    char zDelim[0x80];               /* nul-terminated, so nul not a member */
    int i, j;
    for(i=1, j=0; i<0x80; i++){
      if( !isalnum(i) ){
        zDelim[j++] = i;
      }
    }
    zDelim[j++] = '\0';
    assert( j<=sizeof(zDelim) );
    t->zDelim = string_dup(zDelim);
  }

  *ppTokenizer = &t->base;
  return SQLITE_OK;
}