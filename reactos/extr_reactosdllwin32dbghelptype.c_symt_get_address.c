#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct symt_thunk {int /*<<< orphan*/  address; } ;
struct symt_public {int /*<<< orphan*/  address; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct symt_hierarchy_point {TYPE_3__ loc; struct symt* parent; } ;
struct symt_function {int /*<<< orphan*/  address; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {TYPE_1__ var; } ;
struct symt_data {TYPE_2__ u; int /*<<< orphan*/  kind; } ;
struct symt_compiland {int /*<<< orphan*/  address; } ;
struct symt {int tag; } ;
typedef  int /*<<< orphan*/  ULONG64 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  DataIsFileStatic 137 
#define  DataIsGlobal 136 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  SymTagCompiland 135 
#define  SymTagData 134 
#define  SymTagFuncDebugEnd 133 
#define  SymTagFuncDebugStart 132 
#define  SymTagFunction 131 
#define  SymTagLabel 130 
#define  SymTagPublicSymbol 129 
#define  SymTagThunk 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  symt_get_tag_str (int) ; 

BOOL symt_get_address(const struct symt* type, ULONG64* addr)
{
    switch (type->tag)
    {
    case SymTagData:
        switch (((const struct symt_data*)type)->kind)
        {
        case DataIsGlobal:
        case DataIsFileStatic:
            *addr = ((const struct symt_data*)type)->u.var.offset;
            break;
        default: return FALSE;
        }
        break;
    case SymTagFunction:
        *addr = ((const struct symt_function*)type)->address;
        break;
    case SymTagPublicSymbol:
        *addr = ((const struct symt_public*)type)->address;
        break;
    case SymTagFuncDebugStart:
    case SymTagFuncDebugEnd:
    case SymTagLabel:
        if (!((const struct symt_hierarchy_point*)type)->parent ||
            !symt_get_address(((const struct symt_hierarchy_point*)type)->parent, addr))
            return FALSE;
        *addr += ((const struct symt_hierarchy_point*)type)->loc.offset;
        break;
    case SymTagThunk:
        *addr = ((const struct symt_thunk*)type)->address;
        break;
    case SymTagCompiland:
        *addr = ((const struct symt_compiland*)type)->address;
        break;
    default:
        FIXME("Unsupported sym-tag %s for get-address\n", symt_get_tag_str(type->tag));
        return FALSE;
    }
    return TRUE;
}