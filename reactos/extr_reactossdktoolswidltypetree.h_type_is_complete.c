#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * structure; int /*<<< orphan*/ * enumeration; int /*<<< orphan*/ * iface; int /*<<< orphan*/ * function; } ;
struct TYPE_6__ {TYPE_1__ details; } ;
typedef  TYPE_2__ type_t ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
#define  TYPE_ALIAS 141 
#define  TYPE_ARRAY 140 
#define  TYPE_BASIC 139 
#define  TYPE_BITFIELD 138 
#define  TYPE_COCLASS 137 
#define  TYPE_ENCAPSULATED_UNION 136 
#define  TYPE_ENUM 135 
#define  TYPE_FUNCTION 134 
#define  TYPE_INTERFACE 133 
#define  TYPE_MODULE 132 
#define  TYPE_POINTER 131 
#define  TYPE_STRUCT 130 
#define  TYPE_UNION 129 
#define  TYPE_VOID 128 
 int type_get_type_detect_alias (TYPE_2__ const*) ; 

__attribute__((used)) static inline int type_is_complete(const type_t *type)
{
    switch (type_get_type_detect_alias(type))
    {
    case TYPE_FUNCTION:
        return (type->details.function != NULL);
    case TYPE_INTERFACE:
        return (type->details.iface != NULL);
    case TYPE_ENUM:
        return (type->details.enumeration != NULL);
    case TYPE_UNION:
    case TYPE_ENCAPSULATED_UNION:
    case TYPE_STRUCT:
        return (type->details.structure != NULL);
    case TYPE_VOID:
    case TYPE_BASIC:
    case TYPE_ALIAS:
    case TYPE_MODULE:
    case TYPE_COCLASS:
    case TYPE_POINTER:
    case TYPE_ARRAY:
    case TYPE_BITFIELD:
        return TRUE;
    }
    return FALSE;
}