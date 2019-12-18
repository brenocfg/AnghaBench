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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ sizeuv; } ;
typedef  TYPE_1__ GCproto ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/ * proto_uvinfo (TYPE_1__*) ; 

const char *lj_debug_uvname(GCproto *pt, uint32_t idx)
{
  const uint8_t *p = proto_uvinfo(pt);
  lua_assert(idx < pt->sizeuv);
  if (!p) return "";
  if (idx) while (*p++ || --idx) ;
  return (const char *)p;
}