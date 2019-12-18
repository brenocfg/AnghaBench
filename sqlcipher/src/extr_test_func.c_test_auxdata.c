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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_test_auxdata ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* sqlite3_get_auxdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_set_auxdata (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 char* testContextMalloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_auxdata(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **argv
){
  int i;
  char *zRet = testContextMalloc(pCtx, nArg*2);
  if( !zRet ) return;
  memset(zRet, 0, nArg*2);
  for(i=0; i<nArg; i++){
    char const *z = (char*)sqlite3_value_text(argv[i]);
    if( z ){
      int n;
      char *zAux = sqlite3_get_auxdata(pCtx, i);
      if( zAux ){
        zRet[i*2] = '1';
        assert( strcmp(zAux,z)==0 );
      }else {
        zRet[i*2] = '0';
      }
      n = (int)strlen(z) + 1;
      zAux = testContextMalloc(pCtx, n);
      if( zAux ){
        memcpy(zAux, z, n);
        sqlite3_set_auxdata(pCtx, i, zAux, free_test_auxdata);
      }
      zRet[i*2+1] = ' ';
    }
  }
  sqlite3_result_text(pCtx, zRet, 2*nArg-1, free_test_auxdata);
}