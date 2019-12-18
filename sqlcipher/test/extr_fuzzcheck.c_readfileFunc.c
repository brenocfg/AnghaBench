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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (void*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 
 void* sqlite3_malloc64 (long) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,void*,long,int /*<<< orphan*/  (*) (void*)) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void readfileFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const char *zName;
  FILE *in;
  long nIn;
  void *pBuf;

  zName = (const char*)sqlite3_value_text(argv[0]);
  if( zName==0 ) return;
  in = fopen(zName, "rb");
  if( in==0 ) return;
  fseek(in, 0, SEEK_END);
  nIn = ftell(in);
  rewind(in);
  pBuf = sqlite3_malloc64( nIn );
  if( pBuf && 1==fread(pBuf, nIn, 1, in) ){
    sqlite3_result_blob(context, pBuf, nIn, sqlite3_free);
  }else{
    sqlite3_free(pBuf);
  }
  fclose(in);
}