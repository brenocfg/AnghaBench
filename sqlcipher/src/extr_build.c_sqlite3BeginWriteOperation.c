#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int isMultiWrite; int /*<<< orphan*/  writeMask; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  DbMaskSet (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3CodeVerifySchema (TYPE_1__*,int) ; 
 TYPE_1__* sqlite3ParseToplevel (TYPE_1__*) ; 

void sqlite3BeginWriteOperation(Parse *pParse, int setStatement, int iDb){
  Parse *pToplevel = sqlite3ParseToplevel(pParse);
  sqlite3CodeVerifySchema(pParse, iDb);
  DbMaskSet(pToplevel->writeMask, iDb);
  pToplevel->isMultiWrite |= setStatement;
}