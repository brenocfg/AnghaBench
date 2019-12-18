#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* xAccess ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int (* xOpen ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ;int /*<<< orphan*/  szOsFile; } ;
typedef  TYPE_2__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_11__ {int flags; TYPE_1__* aReal; int /*<<< orphan*/  zName; } ;
typedef  TYPE_3__ multiplexGroup ;
struct TYPE_12__ {TYPE_2__* pOrigVfs; } ;
struct TYPE_9__ {int /*<<< orphan*/ * p; int /*<<< orphan*/  z; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_FULL ; 
 int SQLITE_IOERR_NOMEM ; 
 int SQLITE_MULTIPLEX_JOURNAL_8_3_OFFSET ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 TYPE_8__ gMultiplex ; 
 int multiplexSubFilename (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_log (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_malloc64 (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static sqlite3_file *multiplexSubOpen(
  multiplexGroup *pGroup,    /* The multiplexor group */
  int iChunk,                /* Which chunk to open.  0==original file */
  int *rc,                   /* Result code in and out */
  int *pOutFlags,            /* Output flags */
  int createFlag             /* True to create if iChunk>0 */
){
  sqlite3_file *pSubOpen = 0;
  sqlite3_vfs *pOrigVfs = gMultiplex.pOrigVfs;        /* Real VFS */

#ifdef SQLITE_ENABLE_8_3_NAMES
  /* If JOURNAL_8_3_OFFSET is set to (say) 400, then any overflow files are 
  ** part of a database journal are named db.401, db.402, and so on. A 
  ** database may therefore not grow to larger than 400 chunks. Attempting
  ** to open chunk 401 indicates the database is full. */
  if( iChunk>=SQLITE_MULTIPLEX_JOURNAL_8_3_OFFSET ){
    sqlite3_log(SQLITE_FULL, "multiplexed chunk overflow: %s", pGroup->zName);
    *rc = SQLITE_FULL;
    return 0;
  }
#endif

  *rc = multiplexSubFilename(pGroup, iChunk);
  if( (*rc)==SQLITE_OK && (pSubOpen = pGroup->aReal[iChunk].p)==0 ){
    int flags, bExists;
    flags = pGroup->flags;
    if( createFlag ){
      flags |= SQLITE_OPEN_CREATE;
    }else if( iChunk==0 ){
      /* Fall through */
    }else if( pGroup->aReal[iChunk].z==0 ){
      return 0;
    }else{
      *rc = pOrigVfs->xAccess(pOrigVfs, pGroup->aReal[iChunk].z,
                              SQLITE_ACCESS_EXISTS, &bExists);
     if( *rc || !bExists ){
        if( *rc ){
          sqlite3_log(*rc, "multiplexor.xAccess failure on %s",
                      pGroup->aReal[iChunk].z);
        }
        return 0;
      }
      flags &= ~SQLITE_OPEN_CREATE;
    }
    pSubOpen = sqlite3_malloc64( pOrigVfs->szOsFile );
    if( pSubOpen==0 ){
      *rc = SQLITE_IOERR_NOMEM;
      return 0;
    }
    pGroup->aReal[iChunk].p = pSubOpen;
    *rc = pOrigVfs->xOpen(pOrigVfs, pGroup->aReal[iChunk].z, pSubOpen,
                          flags, pOutFlags);
    if( (*rc)!=SQLITE_OK ){
      sqlite3_log(*rc, "multiplexor.xOpen failure on %s",
                  pGroup->aReal[iChunk].z);
      sqlite3_free(pSubOpen);
      pGroup->aReal[iChunk].p = 0;
      return 0;
    }
  }
  return pSubOpen;
}