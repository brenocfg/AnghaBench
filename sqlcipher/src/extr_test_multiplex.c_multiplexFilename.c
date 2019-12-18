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
 int MX_CHUNK_NUMBER ; 
 scalar_t__ SQLITE_MULTIPLEX_JOURNAL_8_3_OFFSET ; 
 scalar_t__ SQLITE_MULTIPLEX_WAL_8_3_OFFSET ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_WAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int) ; 

__attribute__((used)) static void multiplexFilename(
  const char *zBase,              /* Filename for chunk 0 */
  int nBase,                      /* Size of zBase in bytes (without \0) */
  int flags,                      /* Flags used to open file */
  int iChunk,                     /* Chunk to generate filename for */
  char *zOut                      /* Buffer to write generated name to */
){
  int n = nBase;
  memcpy(zOut, zBase, n+1);
  if( iChunk!=0 && iChunk<=MX_CHUNK_NUMBER ){
#ifdef SQLITE_ENABLE_8_3_NAMES
    int i;
    for(i=n-1; i>0 && i>=n-4 && zOut[i]!='.'; i--){}
    if( i>=n-4 ) n = i+1;
    if( flags & SQLITE_OPEN_MAIN_JOURNAL ){
      /* The extensions on overflow files for main databases are 001, 002,
      ** 003 and so forth.  To avoid name collisions, add 400 to the 
      ** extensions of journal files so that they are 401, 402, 403, ....
      */
      iChunk += SQLITE_MULTIPLEX_JOURNAL_8_3_OFFSET;
    }else if( flags & SQLITE_OPEN_WAL ){
      /* To avoid name collisions, add 700 to the 
      ** extensions of WAL files so that they are 701, 702, 703, ....
      */
      iChunk += SQLITE_MULTIPLEX_WAL_8_3_OFFSET;
    }
#endif
    sqlite3_snprintf(4,&zOut[n],"%03d",iChunk);
    n += 3;
  }

  assert( zOut[n]=='\0' );
  zOut[n+1] = '\0';
}