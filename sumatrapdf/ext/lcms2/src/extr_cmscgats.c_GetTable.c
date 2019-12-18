#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nTable; scalar_t__ TablesCount; int /*<<< orphan*/ * Tab; } ;
typedef  TYPE_1__ cmsIT8 ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  SynError (int /*<<< orphan*/ ,TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static
TABLE* GetTable(cmsContext ContextID, cmsIT8* it8)
{
   if ((it8 -> nTable >= it8 ->TablesCount)) {

           SynError(ContextID, it8, "Table %d out of sequence", it8 -> nTable);
           return it8 -> Tab;
   }

   return it8 ->Tab + it8 ->nTable;
}