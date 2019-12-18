#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_13__ {int mDbFlags; int /*<<< orphan*/  aFunc; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_14__ {char const* zName; scalar_t__ xSFunc; struct TYPE_14__* pNext; scalar_t__ funcFlags; scalar_t__ nArg; } ;
typedef  TYPE_2__ FuncDef ;

/* Variables and functions */
 int DBFLAG_PreferBuiltin ; 
 int FUNC_PERFECT_MATCH ; 
 int SQLITE_FUNC_HASH (scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int matchQuality (TYPE_2__*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* sqlite3DbMallocZero (TYPE_1__*,int) ; 
 TYPE_2__* sqlite3FunctionSearch (int,char const*) ; 
 scalar_t__ sqlite3HashFind (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ sqlite3HashInsert (int /*<<< orphan*/ *,char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_1__*) ; 
 int sqlite3Strlen30 (char const*) ; 
 scalar_t__* sqlite3UpperToLower ; 

FuncDef *sqlite3FindFunction(
  sqlite3 *db,       /* An open database */
  const char *zName, /* Name of the function.  zero-terminated */
  int nArg,          /* Number of arguments.  -1 means any number */
  u8 enc,            /* Preferred text encoding */
  u8 createFlag      /* Create new entry if true and does not otherwise exist */
){
  FuncDef *p;         /* Iterator variable */
  FuncDef *pBest = 0; /* Best match found so far */
  int bestScore = 0;  /* Score of best match */
  int h;              /* Hash value */
  int nName;          /* Length of the name */

  assert( nArg>=(-2) );
  assert( nArg>=(-1) || createFlag==0 );
  nName = sqlite3Strlen30(zName);

  /* First search for a match amongst the application-defined functions.
  */
  p = (FuncDef*)sqlite3HashFind(&db->aFunc, zName);
  while( p ){
    int score = matchQuality(p, nArg, enc);
    if( score>bestScore ){
      pBest = p;
      bestScore = score;
    }
    p = p->pNext;
  }

  /* If no match is found, search the built-in functions.
  **
  ** If the DBFLAG_PreferBuiltin flag is set, then search the built-in
  ** functions even if a prior app-defined function was found.  And give
  ** priority to built-in functions.
  **
  ** Except, if createFlag is true, that means that we are trying to
  ** install a new function.  Whatever FuncDef structure is returned it will
  ** have fields overwritten with new information appropriate for the
  ** new function.  But the FuncDefs for built-in functions are read-only.
  ** So we must not search for built-ins when creating a new function.
  */ 
  if( !createFlag && (pBest==0 || (db->mDbFlags & DBFLAG_PreferBuiltin)!=0) ){
    bestScore = 0;
    h = SQLITE_FUNC_HASH(sqlite3UpperToLower[(u8)zName[0]], nName);
    p = sqlite3FunctionSearch(h, zName);
    while( p ){
      int score = matchQuality(p, nArg, enc);
      if( score>bestScore ){
        pBest = p;
        bestScore = score;
      }
      p = p->pNext;
    }
  }

  /* If the createFlag parameter is true and the search did not reveal an
  ** exact match for the name, number of arguments and encoding, then add a
  ** new entry to the hash table and return it.
  */
  if( createFlag && bestScore<FUNC_PERFECT_MATCH && 
      (pBest = sqlite3DbMallocZero(db, sizeof(*pBest)+nName+1))!=0 ){
    FuncDef *pOther;
    u8 *z;
    pBest->zName = (const char*)&pBest[1];
    pBest->nArg = (u16)nArg;
    pBest->funcFlags = enc;
    memcpy((char*)&pBest[1], zName, nName+1);
    for(z=(u8*)pBest->zName; *z; z++) *z = sqlite3UpperToLower[*z];
    pOther = (FuncDef*)sqlite3HashInsert(&db->aFunc, pBest->zName, pBest);
    if( pOther==pBest ){
      sqlite3DbFree(db, pBest);
      sqlite3OomFault(db);
      return 0;
    }else{
      pBest->pNext = pOther;
    }
  }

  if( pBest && (pBest->xSFunc || createFlag) ){
    return pBest;
  }
  return 0;
}