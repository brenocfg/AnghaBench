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
typedef  scalar_t__ uid_t ;
typedef  int mode_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATHNAME ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_URI ; 
 int SQLITE_OPEN_WAL ; 
 int getFileMode (char const*,int*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int sqlite3Strlen30 (char const*) ; 
 char* sqlite3_uri_parameter (char const*,char*) ; 

__attribute__((used)) static int findCreateFileMode(
  const char *zPath,              /* Path of file (possibly) being created */
  int flags,                      /* Flags passed as 4th argument to xOpen() */
  mode_t *pMode,                  /* OUT: Permissions to open file with */
  uid_t *pUid,                    /* OUT: uid to set on the file */
  gid_t *pGid                     /* OUT: gid to set on the file */
){
  int rc = SQLITE_OK;             /* Return Code */
  *pMode = 0;
  *pUid = 0;
  *pGid = 0;
  if( flags & (SQLITE_OPEN_WAL|SQLITE_OPEN_MAIN_JOURNAL) ){
    char zDb[MAX_PATHNAME+1];     /* Database file path */
    int nDb;                      /* Number of valid bytes in zDb */

    /* zPath is a path to a WAL or journal file. The following block derives
    ** the path to the associated database file from zPath. This block handles
    ** the following naming conventions:
    **
    **   "<path to db>-journal"
    **   "<path to db>-wal"
    **   "<path to db>-journalNN"
    **   "<path to db>-walNN"
    **
    ** where NN is a decimal number. The NN naming schemes are 
    ** used by the test_multiplex.c module.
    */
    nDb = sqlite3Strlen30(zPath) - 1; 
    while( zPath[nDb]!='-' ){
      /* In normal operation, the journal file name will always contain
      ** a '-' character.  However in 8+3 filename mode, or if a corrupt
      ** rollback journal specifies a master journal with a goofy name, then
      ** the '-' might be missing. */
      if( nDb==0 || zPath[nDb]=='.' ) return SQLITE_OK;
      nDb--;
    }
    memcpy(zDb, zPath, nDb);
    zDb[nDb] = '\0';

    rc = getFileMode(zDb, pMode, pUid, pGid);
  }else if( flags & SQLITE_OPEN_DELETEONCLOSE ){
    *pMode = 0600;
  }else if( flags & SQLITE_OPEN_URI ){
    /* If this is a main database file and the file was opened using a URI
    ** filename, check for the "modeof" parameter. If present, interpret
    ** its value as a filename and try to copy the mode, uid and gid from
    ** that file.  */
    const char *z = sqlite3_uri_parameter(zPath, "modeof");
    if( z ){
      rc = getFileMode(z, pMode, pUid, pGid);
  }
  }
  return rc;
}