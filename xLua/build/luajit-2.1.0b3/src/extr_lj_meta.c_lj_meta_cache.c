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
typedef  int /*<<< orphan*/  cTValue ;
struct TYPE_4__ {int /*<<< orphan*/  nomm; } ;
typedef  unsigned int MMS ;
typedef  TYPE_1__ GCtab ;
typedef  int /*<<< orphan*/  GCstr ;

/* Variables and functions */
 unsigned int MM_FAST ; 
 int /*<<< orphan*/ * lj_tab_getstr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ tvisnil (int /*<<< orphan*/ *) ; 

cTValue *lj_meta_cache(GCtab *mt, MMS mm, GCstr *name)
{
  cTValue *mo = lj_tab_getstr(mt, name);
  lua_assert(mm <= MM_FAST);
  if (!mo || tvisnil(mo)) {  /* No metamethod? */
    mt->nomm |= (uint8_t)(1u<<mm);  /* Set negative cache flag. */
    return NULL;
  }
  return mo;
}