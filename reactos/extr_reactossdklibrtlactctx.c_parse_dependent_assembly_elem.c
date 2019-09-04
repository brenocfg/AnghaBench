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
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct assembly_identity {void* delayed; void* optional; } ;
struct actctx_loader {int /*<<< orphan*/  actctx; } ;
typedef  int /*<<< orphan*/  ai ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ,...) ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  add_dependent_assembly_id (struct actctx_loader*,struct assembly_identity*) ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  assemblyIdentityW ; 
 char const* bindingRedirectW ; 
 int /*<<< orphan*/  dependentAssemblyW ; 
 int /*<<< orphan*/  memset (struct assembly_identity*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,void**,void**) ; 
 void* next_xml_elem (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  parse_assembly_identity_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct assembly_identity*) ; 
 void* parse_binding_redirect_elem (int /*<<< orphan*/ *) ; 
 void* parse_end_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_expect_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* parse_unknown_elem (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  xmlstr2unicode (TYPE_1__*) ; 
 void* xmlstr_cmp (TYPE_1__*,char const*) ; 
 scalar_t__ xmlstr_cmp_end (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_dependent_assembly_elem(xmlbuf_t* xmlbuf, struct actctx_loader* acl, BOOL optional)
{
    struct assembly_identity    ai;
    xmlstr_t                    elem, attr_name, attr_value;
    BOOL                        end = FALSE, error = FALSE, ret = TRUE, delayed = FALSE;

    UNICODE_STRING elem1U, elem2U;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        static const WCHAR allowDelayedBindingW[] = {'a','l','l','o','w','D','e','l','a','y','e','d','B','i','n','d','i','n','g',0};
        static const WCHAR trueW[] = {'t','r','u','e',0};

        if (xmlstr_cmp(&attr_name, allowDelayedBindingW))
            delayed = xmlstr_cmp(&attr_value, trueW);
        else
        {
            elem1U = xmlstr2unicode(&attr_name);
            elem2U = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %s=%s\n", &elem1U, &elem2U);
        }
    }

    if (error || end) return end;

    memset(&ai, 0, sizeof(ai));
    ai.optional = optional;
    ai.delayed = delayed;

    if (!parse_expect_elem(xmlbuf, assemblyIdentityW, asmv1W) ||
        !parse_assembly_identity_elem(xmlbuf, acl->actctx, &ai))
        return FALSE;

    //TRACE( "adding name=%s version=%s arch=%s\n", debugstr_w(ai.name), debugstr_version(&ai.version), debugstr_w(ai.arch) );

    /* store the newly found identity for later loading */
    if (!add_dependent_assembly_id(acl, &ai)) return FALSE;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xmlstr_cmp_end(&elem, dependentAssemblyW))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else if (xmlstr_cmp(&elem, bindingRedirectW))
        {
            ret = parse_binding_redirect_elem(xmlbuf);
        }
        else
        {
            DPRINT1("unknown elem %S\n", elem.ptr);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    return ret;
}