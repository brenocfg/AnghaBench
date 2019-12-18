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

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (char*,char const* const,int) ; 
 int /*<<< orphan*/  sqlite3Fts3Dequote (char*) ; 
 char** sqlite3_malloc64 (int) ; 
 scalar_t__ strlen (char const* const) ; 

__attribute__((used)) static int fts3tokDequoteArray(
  int argc,                       /* Number of elements in argv[] */
  const char * const *argv,       /* Input array */
  char ***pazDequote              /* Output array */
){
  int rc = SQLITE_OK;             /* Return code */
  if( argc==0 ){
    *pazDequote = 0;
  }else{
    int i;
    int nByte = 0;
    char **azDequote;

    for(i=0; i<argc; i++){
      nByte += (int)(strlen(argv[i]) + 1);
    }

    *pazDequote = azDequote = sqlite3_malloc64(sizeof(char *)*argc + nByte);
    if( azDequote==0 ){
      rc = SQLITE_NOMEM;
    }else{
      char *pSpace = (char *)&azDequote[argc];
      for(i=0; i<argc; i++){
        int n = (int)strlen(argv[i]);
        azDequote[i] = pSpace;
        memcpy(pSpace, argv[i], n+1);
        sqlite3Fts3Dequote(pSpace);
        pSpace += (n+1);
      }
    }
  }

  return rc;
}