#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prop_type_t ;
struct TYPE_7__ {size_t prop_cnt; TYPE_2__* props; } ;
typedef  TYPE_1__ jsdisp_t ;
struct TYPE_8__ {int /*<<< orphan*/  bucket_head; int /*<<< orphan*/  bucket_next; int /*<<< orphan*/  hash; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ dispex_prop_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 unsigned int get_props_idx (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  resize_props (TYPE_1__*) ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline dispex_prop_t* alloc_prop(jsdisp_t *This, const WCHAR *name, prop_type_t type, DWORD flags)
{
    dispex_prop_t *prop;
    unsigned bucket;

    if(FAILED(resize_props(This)))
        return NULL;

    prop = &This->props[This->prop_cnt];
    prop->name = heap_strdupW(name);
    if(!prop->name)
        return NULL;
    prop->type = type;
    prop->flags = flags;
    prop->hash = string_hash(name);

    bucket = get_props_idx(This, prop->hash);
    prop->bucket_next = This->props[bucket].bucket_head;
    This->props[bucket].bucket_head = This->prop_cnt++;
    return prop;
}