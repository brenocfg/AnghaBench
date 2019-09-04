#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct assembly {scalar_t__ run_level; void* ui_access; } ;
struct actctx_loader {int dummy; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  void* BOOL ;

/* Variables and functions */
 scalar_t__ ACTCTX_RUN_LEVEL_AS_INVOKER ; 
 scalar_t__ ACTCTX_RUN_LEVEL_HIGHEST_AVAILABLE ; 
 scalar_t__ ACTCTX_RUN_LEVEL_REQUIRE_ADMIN ; 
 scalar_t__ ACTCTX_RUN_LEVEL_UNSPECIFIED ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,...) ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  asmv2W ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,void**) ; 
 void* next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* parse_end_element (int /*<<< orphan*/ *) ; 
 void* parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  requestedExecutionLevelW ; 
 scalar_t__ xml_elem_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ xmlstr_cmpi (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static BOOL parse_requested_execution_level_elem(xmlbuf_t* xmlbuf, struct assembly* assembly, struct actctx_loader *acl)
{
    static const WCHAR levelW[] = {'l','e','v','e','l',0};
    static const WCHAR asInvokerW[] = {'a','s','I','n','v','o','k','e','r',0};
    static const WCHAR requireAdministratorW[] = {'r','e','q','u','i','r','e','A','d','m','i','n','i','s','t','r','a','t','o','r',0};
    static const WCHAR highestAvailableW[] = {'h','i','g','h','e','s','t','A','v','a','i','l','a','b','l','e',0};
    static const WCHAR uiAccessW[] = {'u','i','A','c','c','e','s','s',0};
    static const WCHAR falseW[] = {'f','a','l','s','e',0};
    static const WCHAR trueW[] = {'t','r','u','e',0};

    xmlstr_t attr_name, attr_value, elem;
    BOOL end = FALSE, ret = TRUE, error;

    /* Multiple requestedExecutionLevel elements are not supported. */
    if (assembly->run_level != ACTCTX_RUN_LEVEL_UNSPECIFIED)
        return FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        UNICODE_STRING attr_nameU = xmlstr2unicode(&attr_name);
        UNICODE_STRING attr_valueU = xmlstr2unicode(&attr_value);
        if (xmlstr_cmp(&attr_name, levelW))
        {
            if (xmlstr_cmpi(&attr_value, asInvokerW))
                assembly->run_level = ACTCTX_RUN_LEVEL_AS_INVOKER;
            else if (xmlstr_cmpi(&attr_value, highestAvailableW))
                assembly->run_level = ACTCTX_RUN_LEVEL_HIGHEST_AVAILABLE;
            else if (xmlstr_cmpi(&attr_value, requireAdministratorW))
                assembly->run_level = ACTCTX_RUN_LEVEL_REQUIRE_ADMIN;
            else
                DPRINT1("unknown execution level: %wZ\n", &attr_valueU);
        }
        else if (xmlstr_cmp(&attr_name, uiAccessW))
        {
            if (xmlstr_cmpi(&attr_value, falseW))
                assembly->ui_access = FALSE;
            else if (xmlstr_cmpi(&attr_value, trueW))
                assembly->ui_access = TRUE;
            else
                DPRINT1("unknown uiAccess value: %wZ\n", &attr_valueU);
        }
        else
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
    }

    if (error) return FALSE;
    if (end) return TRUE;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xml_elem_cmp_end(&elem, requestedExecutionLevelW, asmv2W))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else
        {
            UNICODE_STRING elemU = xmlstr2unicode(&elem);
            DPRINT1("unknown element %wZ\n", &elemU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    return ret;
}