#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UUID ;
struct TYPE_3__ {int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ RpcObjTypeMap ;

/* Variables and functions */
 TYPE_1__* LookupObjTypeMap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_nil ; 

__attribute__((used)) static inline UUID *LookupObjType(UUID *ObjUuid)
{
  RpcObjTypeMap *map = LookupObjTypeMap(ObjUuid);
  if (map)
    return &map->Type;
  else
    return &uuid_nil;
}