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
struct sltg_typelib {int dummy; } ;

/* Variables and functions */
#define  TYPE_BASIC 134 
#define  TYPE_COCLASS 133 
#define  TYPE_ENUM 132 
#define  TYPE_INTERFACE 131 
#define  TYPE_POINTER 130 
#define  TYPE_STRUCT 129 
#define  TYPE_UNION 128 
 int /*<<< orphan*/  add_coclass_typeinfo (struct sltg_typelib*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_enum_typeinfo (struct sltg_typelib*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_interface_typeinfo (struct sltg_typelib*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_structure_typeinfo (struct sltg_typelib*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_union_typeinfo (struct sltg_typelib*,TYPE_1__*) ; 
 int /*<<< orphan*/  chat (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 int type_get_type (TYPE_1__*) ; 

__attribute__((used)) static void add_type_typeinfo(struct sltg_typelib *typelib, type_t *type)
{
    chat("add_type_typeinfo: adding %s, type %d\n", type->name, type_get_type(type));

    switch (type_get_type(type))
    {
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
        break;
    default:
        error("add_type_typeinfo: unhandled type %d for %s\n", type_get_type(type), type->name);
        break;
    }
}