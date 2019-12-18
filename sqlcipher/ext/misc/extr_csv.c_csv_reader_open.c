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
struct TYPE_5__ {char* zIn; scalar_t__ in; int /*<<< orphan*/  nIn; } ;
typedef  TYPE_1__ CsvReader ;

/* Variables and functions */
 int /*<<< orphan*/  CSV_INBUFSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  csv_errmsg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  csv_reader_reset (TYPE_1__*) ; 
 scalar_t__ fopen (char const*,char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int csv_reader_open(
  CsvReader *p,               /* The reader to open */
  const char *zFilename,      /* Read from this filename */
  const char *zData           /*  ... or use this data */
){
  if( zFilename ){
    p->zIn = sqlite3_malloc( CSV_INBUFSZ );
    if( p->zIn==0 ){
      csv_errmsg(p, "out of memory");
      return 1;
    }
    p->in = fopen(zFilename, "rb");
    if( p->in==0 ){
      sqlite3_free(p->zIn);
      csv_reader_reset(p);
      csv_errmsg(p, "cannot open '%s' for reading", zFilename);
      return 1;
    }
  }else{
    assert( p->in==0 );
    p->zIn = (char*)zData;
    p->nIn = strlen(zData);
  }
  return 0;
}