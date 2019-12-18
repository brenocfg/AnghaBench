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
struct actctx_loader {int dummy; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,...) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  dependencyW ; 
 int /*<<< orphan*/  dependentAssemblyW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optionalW ; 
 scalar_t__ parse_dependent_assembly_elem (int /*<<< orphan*/ *,struct actctx_loader*,scalar_t__) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesW ; 

__attribute__((used)) static BOOL parse_dependency_elem(xmlbuf_t* xmlbuf, struct actctx_loader* acl)
{
    xmlstr_t attr_name, attr_value, elem;
    UNICODE_STRING attr_nameU, attr_valueU;
    BOOL end = FALSE, ret = TRUE, error, optional = FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        attr_nameU = xmlstr2unicode(&attr_name);
        attr_valueU = xmlstr2unicode(&attr_value);

        if (xmlstr_cmp(&attr_name, optionalW))
        {
            optional = xmlstr_cmpi( &attr_value, yesW );
            DPRINT1("optional=%wZ\n", &attr_valueU);
        }
        else
        {
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xmlstr_cmp_end(&elem, dependencyW))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else if (xmlstr_cmp(&elem, dependentAssemblyW))
        {
            ret = parse_dependent_assembly_elem(xmlbuf, acl, optional);
        }
        else
        {
            attr_nameU = xmlstr2unicode(&elem);
            DPRINT1("unknown element %wZ\n", &attr_nameU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    return ret;
}