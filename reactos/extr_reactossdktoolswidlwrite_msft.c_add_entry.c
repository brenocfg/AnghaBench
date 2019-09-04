#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
struct TYPE_8__ {TYPE_4__* type; struct TYPE_8__* next; } ;
typedef  TYPE_2__ type_list_t ;
struct TYPE_7__ {int /*<<< orphan*/ * type; TYPE_2__* type_list; } ;
struct TYPE_9__ {int type; TYPE_1__ u; } ;
typedef  TYPE_3__ statement_t ;
typedef  int /*<<< orphan*/  msft_typelib_t ;
struct TYPE_10__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_PUBLIC ; 
#define  STMT_CPPQUOTE 137 
#define  STMT_DECLARATION 136 
#define  STMT_IMPORT 135 
#define  STMT_IMPORTLIB 134 
#define  STMT_LIBRARY 133 
#define  STMT_MODULE 132 
#define  STMT_PRAGMA 131 
#define  STMT_TYPE 130 
#define  STMT_TYPEDEF 129 
#define  STMT_TYPEREF 128 
 int /*<<< orphan*/  add_module_typeinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_type_typeinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_typedef_typeinfo (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  is_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * type_alias_get_aliasee (TYPE_4__*) ; 

__attribute__((used)) static void add_entry(msft_typelib_t *typelib, const statement_t *stmt)
{
    switch(stmt->type) {
    case STMT_LIBRARY:
    case STMT_IMPORT:
    case STMT_PRAGMA:
    case STMT_CPPQUOTE:
    case STMT_DECLARATION:
        /* not included in typelib */
        break;
    case STMT_IMPORTLIB:
        /* not processed here */
        break;
    case STMT_TYPEDEF:
    {
        const type_list_t *type_entry = stmt->u.type_list;
        for (; type_entry; type_entry = type_entry->next) {
            /* if the type is public then add the typedef, otherwise attempt
             * to add the aliased type */
            if (is_attr(type_entry->type->attrs, ATTR_PUBLIC))
                add_typedef_typeinfo(typelib, type_entry->type);
            else
                add_type_typeinfo(typelib, type_alias_get_aliasee(type_entry->type));
        }
        break;
    }
    case STMT_MODULE:
        add_module_typeinfo(typelib, stmt->u.type);
        break;
    case STMT_TYPE:
    case STMT_TYPEREF:
    {
        type_t *type = stmt->u.type;
        add_type_typeinfo(typelib, type);
        break;
    }
    }
}