#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_t ;
struct TYPE_6__ {int /*<<< orphan*/ * type; struct TYPE_6__* next; } ;
typedef  TYPE_2__ type_list_t ;
struct sltg_typelib {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * type; TYPE_2__* type_list; } ;
struct TYPE_7__ {int type; TYPE_1__ u; } ;
typedef  TYPE_3__ statement_t ;

/* Variables and functions */
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
 int /*<<< orphan*/  add_module_typeinfo (struct sltg_typelib*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_type_typeinfo (struct sltg_typelib*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,int) ; 

__attribute__((used)) static void add_statement(struct sltg_typelib *typelib, const statement_t *stmt)
{
    switch(stmt->type)
    {
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
        for (; type_entry; type_entry = type_entry->next)
        {
            /* in old style typelibs all types are public */
            add_type_typeinfo(typelib, type_entry->type);
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

    default:
        error("add_statement: unhandled statement type %d\n", stmt->type);
        break;
    }
}