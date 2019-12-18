#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  TagObject ;
struct TYPE_4__ {size_t type; } ;
struct TYPE_5__ {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  ObjectHeader ;
typedef  TYPE_2__ Object ;
typedef  int /*<<< orphan*/  HashTableObject ;
typedef  int /*<<< orphan*/  FieldObject ;
typedef  int /*<<< orphan*/  EntryObject ;
typedef  int /*<<< orphan*/  EntryArrayObject ;
typedef  int /*<<< orphan*/  DataObject ;

/* Variables and functions */
 size_t ELEMENTSOF (int const*) ; 
#define  OBJECT_DATA 134 
#define  OBJECT_DATA_HASH_TABLE 133 
#define  OBJECT_ENTRY 132 
#define  OBJECT_ENTRY_ARRAY 131 
#define  OBJECT_FIELD 130 
#define  OBJECT_FIELD_HASH_TABLE 129 
#define  OBJECT_TAG 128 

__attribute__((used)) static uint64_t minimum_header_size(Object *o) {

        static const uint64_t table[] = {
                [OBJECT_DATA] = sizeof(DataObject),
                [OBJECT_FIELD] = sizeof(FieldObject),
                [OBJECT_ENTRY] = sizeof(EntryObject),
                [OBJECT_DATA_HASH_TABLE] = sizeof(HashTableObject),
                [OBJECT_FIELD_HASH_TABLE] = sizeof(HashTableObject),
                [OBJECT_ENTRY_ARRAY] = sizeof(EntryArrayObject),
                [OBJECT_TAG] = sizeof(TagObject),
        };

        if (o->object.type >= ELEMENTSOF(table) || table[o->object.type] <= 0)
                return sizeof(ObjectHeader);

        return table[o->object.type];
}