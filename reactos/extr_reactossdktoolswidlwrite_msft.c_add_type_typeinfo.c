#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* name; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  msft_typelib_t ;

/* Variables and functions */
#define  TYPE_ARRAY 135 
#define  TYPE_BASIC 134 
#define  TYPE_COCLASS 133 
#define  TYPE_ENUM 132 
#define  TYPE_INTERFACE 131 
#define  TYPE_POINTER 130 
#define  TYPE_STRUCT 129 
#define  TYPE_UNION 128 
 int /*<<< orphan*/  add_coclass_typeinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  add_enum_typeinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  add_interface_typeinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  add_structure_typeinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  add_union_typeinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int type_get_type (TYPE_1__*) ; 

__attribute__((used)) static void add_type_typeinfo(msft_typelib_t *typelib, type_t *type)
{
    switch (type_get_type(type)) {
    case TYPE_INTERFACE:
        add_interface_typeinfo(typelib, type);
        break;
    case TYPE_STRUCT:
        add_structure_typeinfo(typelib, type);
        break;
    case TYPE_ENUM:
        add_enum_typeinfo(typelib, type);
        break;
    case TYPE_UNION:
        add_union_typeinfo(typelib, type);
        break;
    case TYPE_COCLASS:
        add_coclass_typeinfo(typelib, type);
        break;
    case TYPE_BASIC:
    case TYPE_POINTER:
    case TYPE_ARRAY:
        break;
    default:
        error("add_entry: unhandled type 0x%x for %s\n",
              type_get_type(type), type->name);
        break;
    }
}