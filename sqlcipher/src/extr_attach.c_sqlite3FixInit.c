#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nDb; TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_10__ {char const* zType; int bVarOnly; int /*<<< orphan*/  const* pName; int /*<<< orphan*/  pSchema; int /*<<< orphan*/  zDb; TYPE_3__* pParse; } ;
struct TYPE_9__ {TYPE_2__* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  pSchema; int /*<<< orphan*/  zDbSName; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ DbFixer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void sqlite3FixInit(
  DbFixer *pFix,      /* The fixer to be initialized */
  Parse *pParse,      /* Error messages will be written here */
  int iDb,            /* This is the database that must be used */
  const char *zType,  /* "view", "trigger", or "index" */
  const Token *pName  /* Name of the view, trigger, or index */
){
  sqlite3 *db;

  db = pParse->db;
  assert( db->nDb>iDb );
  pFix->pParse = pParse;
  pFix->zDb = db->aDb[iDb].zDbSName;
  pFix->pSchema = db->aDb[iDb].pSchema;
  pFix->zType = zType;
  pFix->pName = pName;
  pFix->bVarOnly = (iDb==1);
}