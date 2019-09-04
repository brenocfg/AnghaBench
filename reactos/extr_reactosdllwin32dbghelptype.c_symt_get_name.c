#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char const* name; } ;
struct symt_udt {TYPE_6__ hash_elt; } ;
struct TYPE_13__ {char const* name; } ;
struct symt_typedef {TYPE_5__ hash_elt; } ;
struct TYPE_12__ {char const* name; } ;
struct symt_thunk {TYPE_4__ hash_elt; } ;
struct TYPE_9__ {char const* name; } ;
struct symt_public {TYPE_1__ hash_elt; } ;
struct TYPE_11__ {char const* name; } ;
struct symt_hierarchy_point {TYPE_3__ hash_elt; } ;
struct TYPE_16__ {char const* name; } ;
struct symt_function {TYPE_8__ hash_elt; } ;
struct symt_enum {char const* name; } ;
struct TYPE_15__ {char const* name; } ;
struct symt_data {TYPE_7__ hash_elt; } ;
struct TYPE_10__ {char const* name; } ;
struct symt_basic {TYPE_2__ hash_elt; } ;
struct symt {int tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  SymTagArrayType 139 
#define  SymTagBaseType 138 
#define  SymTagData 137 
#define  SymTagEnum 136 
#define  SymTagFunction 135 
#define  SymTagFunctionType 134 
#define  SymTagLabel 133 
#define  SymTagPointerType 132 
#define  SymTagPublicSymbol 131 
#define  SymTagThunk 130 
#define  SymTagTypedef 129 
#define  SymTagUDT 128 
 int /*<<< orphan*/  symt_get_tag_str (int) ; 

const char* symt_get_name(const struct symt* sym)
{
    switch (sym->tag)
    {
    /* lexical tree */
    case SymTagData:            return ((const struct symt_data*)sym)->hash_elt.name;
    case SymTagFunction:        return ((const struct symt_function*)sym)->hash_elt.name;
    case SymTagPublicSymbol:    return ((const struct symt_public*)sym)->hash_elt.name;
    case SymTagBaseType:        return ((const struct symt_basic*)sym)->hash_elt.name;
    case SymTagLabel:           return ((const struct symt_hierarchy_point*)sym)->hash_elt.name;
    case SymTagThunk:           return ((const struct symt_thunk*)sym)->hash_elt.name;
    /* hierarchy tree */
    case SymTagEnum:            return ((const struct symt_enum*)sym)->name;
    case SymTagTypedef:         return ((const struct symt_typedef*)sym)->hash_elt.name;
    case SymTagUDT:             return ((const struct symt_udt*)sym)->hash_elt.name;
    default:
        FIXME("Unsupported sym-tag %s\n", symt_get_tag_str(sym->tag));
        /* fall through */
    case SymTagArrayType:
    case SymTagPointerType:
    case SymTagFunctionType:
        return NULL;
    }
}