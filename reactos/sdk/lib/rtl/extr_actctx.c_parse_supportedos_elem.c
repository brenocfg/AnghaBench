#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ len; scalar_t__ ptr; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct assembly {int dummy; } ;
struct actctx_loader {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
struct TYPE_13__ {int Length; int MaximumLength; scalar_t__ Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
struct TYPE_14__ {int /*<<< orphan*/  Id; int /*<<< orphan*/  Type; } ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_3__ COMPATIBILITY_CONTEXT_ELEMENT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTCX_COMPATIBILITY_ELEMENT_TYPE_OS ; 
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_2__*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IdW ; 
 scalar_t__ RtlGUIDFromString (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 
 TYPE_3__* add_compat_context (struct assembly*) ; 
 int /*<<< orphan*/  asmv1W ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supportedOSW ; 
 TYPE_2__ xmlstr2unicode (TYPE_1__*) ; 
 scalar_t__ xmlstr_cmp (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_supportedos_elem(xmlbuf_t *xmlbuf, struct assembly *assembly, struct actctx_loader *acl)
{
    xmlstr_t attr_name, attr_value;
    BOOL end = FALSE, error;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, IdW))
        {
            COMPATIBILITY_CONTEXT_ELEMENT *compat;
            UNICODE_STRING str;
            GUID compat_id;

            str.Buffer = (PWSTR)attr_value.ptr;
            str.Length = str.MaximumLength = (USHORT)attr_value.len * sizeof(WCHAR);
            if (RtlGUIDFromString(&str, &compat_id) == STATUS_SUCCESS)
            {
                if (!(compat = add_compat_context(assembly))) return FALSE;
                compat->Type = ACTCX_COMPATIBILITY_ELEMENT_TYPE_OS;
                compat->Id = compat_id;
            }
            else
            {
                UNICODE_STRING attr_valueU = xmlstr2unicode(&attr_value);
                DPRINT1("Invalid guid %wZ\n", &attr_valueU);
            }
        }
        else
        {
            UNICODE_STRING attr_nameU = xmlstr2unicode(&attr_name);
            UNICODE_STRING attr_valueU = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error) return FALSE;
    if (end) return TRUE;

    return parse_expect_end_elem(xmlbuf, supportedOSW, asmv1W);
}