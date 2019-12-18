#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* db; scalar_t__ nErr; } ;
struct TYPE_13__ {int selFlags; } ;
struct TYPE_12__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_2__ Select ;
typedef  TYPE_3__ Parse ;
typedef  int /*<<< orphan*/  NameContext ;

/* Variables and functions */
 int SF_HasTypeInfo ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ResolveSelectNames (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3SelectAddTypeInfo (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3SelectExpand (TYPE_3__*,TYPE_2__*) ; 

void sqlite3SelectPrep(
  Parse *pParse,         /* The parser context */
  Select *p,             /* The SELECT statement being coded. */
  NameContext *pOuterNC  /* Name context for container */
){
  assert( p!=0 || pParse->db->mallocFailed );
  if( pParse->db->mallocFailed ) return;
  if( p->selFlags & SF_HasTypeInfo ) return;
  sqlite3SelectExpand(pParse, p);
  if( pParse->nErr || pParse->db->mallocFailed ) return;
  sqlite3ResolveSelectNames(pParse, p, pOuterNC);
  if( pParse->nErr || pParse->db->mallocFailed ) return;
  sqlite3SelectAddTypeInfo(pParse, p);
}