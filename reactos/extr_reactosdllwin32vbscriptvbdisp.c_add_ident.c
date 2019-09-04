#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  const* name; } ;
typedef  TYPE_1__ ident_map_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {int ident_map_size; int ident_map_cnt; TYPE_1__* ident_map; } ;
typedef  TYPE_2__ ScriptDisp ;

/* Variables and functions */
 TYPE_1__* heap_alloc (int) ; 
 TYPE_1__* heap_realloc (TYPE_1__*,int) ; 

__attribute__((used)) static ident_map_t *add_ident(ScriptDisp *This, const WCHAR *name)
{
    ident_map_t *ret;

    if(!This->ident_map_size) {
        This->ident_map = heap_alloc(4 * sizeof(*This->ident_map));
        if(!This->ident_map)
            return NULL;
        This->ident_map_size = 4;
    }else if(This->ident_map_cnt == This->ident_map_size) {
        ident_map_t *new_map;

        new_map = heap_realloc(This->ident_map, 2*This->ident_map_size*sizeof(*new_map));
        if(!new_map)
            return NULL;
        This->ident_map = new_map;
        This->ident_map_size *= 2;
    }

    ret = This->ident_map + This->ident_map_cnt++;
    ret->name = name;
    return ret;
}