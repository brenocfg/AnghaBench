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
typedef  int /*<<< orphan*/  UUID ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  Object; } ;
typedef  TYPE_1__ RpcObjTypeMap ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 TYPE_1__* RpcObjTypeMaps ; 
 int /*<<< orphan*/  UuidCompare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline RpcObjTypeMap *LookupObjTypeMap(UUID *ObjUuid)
{
  RpcObjTypeMap *rslt = RpcObjTypeMaps;
  RPC_STATUS dummy;

  while (rslt) {
    if (! UuidCompare(ObjUuid, &rslt->Object, &dummy)) break;
    rslt = rslt->next;
  }

  return rslt;
}