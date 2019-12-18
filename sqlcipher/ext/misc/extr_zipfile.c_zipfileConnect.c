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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {char* zFile; int /*<<< orphan*/ * aBuffer; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ ZipfileTab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int ZIPFILE_BUFFER_SIZE ; 
 int /*<<< orphan*/  ZIPFILE_SCHEMA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_malloc64 (scalar_t__) ; 
 char* sqlite3_mprintf (char*) ; 
 scalar_t__ sqlite3_stricmp (char const* const,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  zipfileDequote (char*) ; 

__attribute__((used)) static int zipfileConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  int nByte = sizeof(ZipfileTab) + ZIPFILE_BUFFER_SIZE;
  int nFile = 0;
  const char *zFile = 0;
  ZipfileTab *pNew = 0;
  int rc;

  /* If the table name is not "zipfile", require that the argument be
  ** specified. This stops zipfile tables from being created as:
  **
  **   CREATE VIRTUAL TABLE zzz USING zipfile();
  **
  ** It does not prevent:
  **
  **   CREATE VIRTUAL TABLE zipfile USING zipfile();
  */
  assert( 0==sqlite3_stricmp(argv[0], "zipfile") );
  if( (0!=sqlite3_stricmp(argv[2], "zipfile") && argc<4) || argc>4 ){
    *pzErr = sqlite3_mprintf("zipfile constructor requires one argument");
    return SQLITE_ERROR;
  }

  if( argc>3 ){
    zFile = argv[3];
    nFile = (int)strlen(zFile)+1;
  }

  rc = sqlite3_declare_vtab(db, ZIPFILE_SCHEMA);
  if( rc==SQLITE_OK ){
    pNew = (ZipfileTab*)sqlite3_malloc64((sqlite3_int64)nByte+nFile);
    if( pNew==0 ) return SQLITE_NOMEM;
    memset(pNew, 0, nByte+nFile);
    pNew->db = db;
    pNew->aBuffer = (u8*)&pNew[1];
    if( zFile ){
      pNew->zFile = (char*)&pNew->aBuffer[ZIPFILE_BUFFER_SIZE];
      memcpy(pNew->zFile, zFile, nFile);
      zipfileDequote(pNew->zFile);
    }
  }
  *ppVtab = (sqlite3_vtab*)pNew;
  return rc;
}