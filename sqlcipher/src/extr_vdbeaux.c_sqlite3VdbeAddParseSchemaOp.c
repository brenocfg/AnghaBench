#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* db; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_6__ {int nDb; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ParseSchema ; 
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeUsesBtree (TYPE_2__*,int) ; 

void sqlite3VdbeAddParseSchemaOp(Vdbe *p, int iDb, char *zWhere){
  int j;
  sqlite3VdbeAddOp4(p, OP_ParseSchema, iDb, 0, 0, zWhere, P4_DYNAMIC);
  for(j=0; j<p->db->nDb; j++) sqlite3VdbeUsesBtree(p, j);
}