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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_4__ {int /*<<< orphan*/  dlw; int /*<<< orphan*/  plw; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  DocListType ;
typedef  TYPE_1__ DLCollector ;

/* Variables and functions */
 int /*<<< orphan*/  dataBufferInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlwInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plwInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3_malloc (int) ; 

__attribute__((used)) static DLCollector *dlcNew(sqlite_int64 iDocid, DocListType iType){
  DLCollector *pCollector = sqlite3_malloc(sizeof(DLCollector));
  dataBufferInit(&pCollector->b, 0);
  dlwInit(&pCollector->dlw, iType, &pCollector->b);
  plwInit(&pCollector->plw, &pCollector->dlw, iDocid);
  return pCollector;
}