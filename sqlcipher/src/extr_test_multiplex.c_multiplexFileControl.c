#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_12__ {unsigned char bEnabled; unsigned int szChunk; int bTruncate; } ;
typedef  TYPE_3__ multiplexGroup ;
struct TYPE_13__ {TYPE_3__* pGroup; } ;
typedef  TYPE_4__ multiplexConn ;
struct TYPE_14__ {int /*<<< orphan*/  isInitialized; } ;
struct TYPE_10__ {int (* xFileControl ) (TYPE_2__*,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PAGE_SIZE ; 
#define  MULTIPLEX_CTRL_ENABLE 133 
#define  MULTIPLEX_CTRL_SET_CHUNK_SIZE 132 
#define  MULTIPLEX_CTRL_SET_MAX_CHUNKS 131 
 int SQLITE_ERROR ; 
#define  SQLITE_FCNTL_CHUNK_SIZE 130 
#define  SQLITE_FCNTL_PRAGMA 129 
#define  SQLITE_FCNTL_SIZE_HINT 128 
 int SQLITE_FCNTL_VFSNAME ; 
 int SQLITE_MISUSE ; 
 int SQLITE_OK ; 
 TYPE_9__ gMultiplex ; 
 TYPE_2__* multiplexSubOpen (TYPE_3__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_mprintf (char*,...) ; 
 int /*<<< orphan*/  sqlite3_stricmp (char*,char*) ; 
 int stub1 (TYPE_2__*,int,void*) ; 

__attribute__((used)) static int multiplexFileControl(sqlite3_file *pConn, int op, void *pArg){
  multiplexConn *p = (multiplexConn*)pConn;
  multiplexGroup *pGroup = p->pGroup;
  int rc = SQLITE_ERROR;
  sqlite3_file *pSubOpen;

  if( !gMultiplex.isInitialized ) return SQLITE_MISUSE;
  switch( op ){
    case MULTIPLEX_CTRL_ENABLE:
      if( pArg ) {
        int bEnabled = *(int *)pArg;
        pGroup->bEnabled = (unsigned char)bEnabled;
        rc = SQLITE_OK;
      }
      break;
    case MULTIPLEX_CTRL_SET_CHUNK_SIZE:
      if( pArg ) {
        unsigned int szChunk = *(unsigned*)pArg;
        if( szChunk<1 ){
          rc = SQLITE_MISUSE;
        }else{
          /* Round up to nearest multiple of MAX_PAGE_SIZE. */
          szChunk = (szChunk + (MAX_PAGE_SIZE-1));
          szChunk &= ~(MAX_PAGE_SIZE-1);
          pGroup->szChunk = szChunk;
          rc = SQLITE_OK;
        }
      }
      break;
    case MULTIPLEX_CTRL_SET_MAX_CHUNKS:
      rc = SQLITE_OK;
      break;
    case SQLITE_FCNTL_SIZE_HINT:
    case SQLITE_FCNTL_CHUNK_SIZE:
      /* no-op these */
      rc = SQLITE_OK;
      break;
    case SQLITE_FCNTL_PRAGMA: {
      char **aFcntl = (char**)pArg;
      /*
      ** EVIDENCE-OF: R-29875-31678 The argument to the SQLITE_FCNTL_PRAGMA
      ** file control is an array of pointers to strings (char**) in which the
      ** second element of the array is the name of the pragma and the third
      ** element is the argument to the pragma or NULL if the pragma has no
      ** argument.
      */
      if( aFcntl[1] && sqlite3_stricmp(aFcntl[1],"multiplex_truncate")==0 ){
        if( aFcntl[2] && aFcntl[2][0] ){
          if( sqlite3_stricmp(aFcntl[2], "on")==0
           || sqlite3_stricmp(aFcntl[2], "1")==0 ){
            pGroup->bTruncate = 1;
          }else
          if( sqlite3_stricmp(aFcntl[2], "off")==0
           || sqlite3_stricmp(aFcntl[2], "0")==0 ){
            pGroup->bTruncate = 0;
          }
        }
        /* EVIDENCE-OF: R-27806-26076 The handler for an SQLITE_FCNTL_PRAGMA
        ** file control can optionally make the first element of the char**
        ** argument point to a string obtained from sqlite3_mprintf() or the
        ** equivalent and that string will become the result of the pragma
        ** or the error message if the pragma fails.
        */
        aFcntl[0] = sqlite3_mprintf(pGroup->bTruncate ? "on" : "off");
        rc = SQLITE_OK;
        break;
      }
      /* If the multiplexor does not handle the pragma, pass it through
      ** into the default case. */
    }
    default:
      pSubOpen = multiplexSubOpen(pGroup, 0, &rc, NULL, 0);
      if( pSubOpen ){
        rc = pSubOpen->pMethods->xFileControl(pSubOpen, op, pArg);
        if( op==SQLITE_FCNTL_VFSNAME && rc==SQLITE_OK ){
         *(char**)pArg = sqlite3_mprintf("multiplex/%z", *(char**)pArg);
        }
      }
      break;
  }
  return rc;
}