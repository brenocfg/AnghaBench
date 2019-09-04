#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int len; } ;
struct TYPE_6__ {unsigned char* list; } ;
union codeview_reftype {TYPE_2__ generic; TYPE_1__ fieldlist; } ;
struct TYPE_10__ {int id; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
union codeview_fieldtype {TYPE_5__ generic; TYPE_4__ enumerate_v3; TYPE_3__ enumerate_v1; } ;
struct symt_enum {int dummy; } ;
struct p_string {int /*<<< orphan*/  namelen; } ;
struct module {int dummy; } ;
typedef  unsigned char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  LF_ENUMERATE_V1 129 
#define  LF_ENUMERATE_V3 128 
 int /*<<< orphan*/  TRUE ; 
 int numeric_leaf (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  symt_add_enum_element (struct module*,struct symt_enum*,char const*,int) ; 
 char const* terminate_string (struct p_string const*) ; 

__attribute__((used)) static BOOL codeview_add_type_enum_field_list(struct module* module,
                                              struct symt_enum* symt,
                                              const union codeview_reftype* ref_type)
{
    const unsigned char*                ptr = ref_type->fieldlist.list;
    const unsigned char*                last = (const BYTE*)ref_type + ref_type->generic.len + 2;
    const union codeview_fieldtype*     type;

    while (ptr < last)
    {
        if (*ptr >= 0xf0)       /* LF_PAD... */
        {
            ptr += *ptr & 0x0f;
            continue;
        }

        type = (const union codeview_fieldtype*)ptr;

        switch (type->generic.id)
        {
        case LF_ENUMERATE_V1:
        {
            int value, vlen = numeric_leaf(&value, &type->enumerate_v1.value);
            const struct p_string* p_name = (const struct p_string*)((const unsigned char*)&type->enumerate_v1.value + vlen);

            symt_add_enum_element(module, symt, terminate_string(p_name), value);
            ptr += 2 + 2 + vlen + (1 + p_name->namelen);
            break;
        }
        case LF_ENUMERATE_V3:
        {
            int value, vlen = numeric_leaf(&value, &type->enumerate_v3.value);
            const char* name = (const char*)&type->enumerate_v3.value + vlen;

            symt_add_enum_element(module, symt, name, value);
            ptr += 2 + 2 + vlen + (1 + strlen(name));
            break;
        }

        default:
            FIXME("Unsupported type %04x in ENUM field list\n", type->generic.id);
            return FALSE;
        }
    }
    return TRUE;
}