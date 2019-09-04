#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* type_hierarchy; int /*<<< orphan*/  type_descriptor; int /*<<< orphan*/  flags; int /*<<< orphan*/  base_class_offset; int /*<<< orphan*/  signature; } ;
typedef  TYPE_4__ rtti_object_locator ;
struct TYPE_11__ {int array_len; TYPE_2__* base_classes; int /*<<< orphan*/  attributes; int /*<<< orphan*/  signature; } ;
typedef  TYPE_5__ rtti_object_hierarchy ;
struct TYPE_7__ {int /*<<< orphan*/  vbase_offset; int /*<<< orphan*/  vbase_descr; int /*<<< orphan*/  this_offset; } ;
struct TYPE_9__ {int /*<<< orphan*/  type_descriptor; int /*<<< orphan*/  attributes; TYPE_1__ offsets; int /*<<< orphan*/  num_base_classes; } ;
struct TYPE_8__ {TYPE_3__** bases; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  dbgstr_type_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_obj_locator( const rtti_object_locator *ptr )
{
    int i;
    const rtti_object_hierarchy *h = ptr->type_hierarchy;

    TRACE( "%p: sig=%08x base_offset=%08x flags=%08x type=%p %s hierarchy=%p\n",
           ptr, ptr->signature, ptr->base_class_offset, ptr->flags,
           ptr->type_descriptor, dbgstr_type_info(ptr->type_descriptor), ptr->type_hierarchy );
    TRACE( "  hierarchy: sig=%08x attr=%08x len=%d base classes=%p\n",
           h->signature, h->attributes, h->array_len, h->base_classes );
    for (i = 0; i < h->array_len; i++)
    {
        TRACE( "    base class %p: num %d off %d,%d,%d attr %08x type %p %s\n",
               h->base_classes->bases[i],
               h->base_classes->bases[i]->num_base_classes,
               h->base_classes->bases[i]->offsets.this_offset,
               h->base_classes->bases[i]->offsets.vbase_descr,
               h->base_classes->bases[i]->offsets.vbase_offset,
               h->base_classes->bases[i]->attributes,
               h->base_classes->bases[i]->type_descriptor,
               dbgstr_type_info(h->base_classes->bases[i]->type_descriptor) );
    }
}