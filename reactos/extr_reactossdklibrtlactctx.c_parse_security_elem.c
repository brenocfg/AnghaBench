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
struct assembly {int dummy; } ;
struct actctx_loader {int dummy; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  asmv2W ; 
 scalar_t__ next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_requested_privileges_elem (int /*<<< orphan*/ *,struct assembly*,struct actctx_loader*) ; 
 scalar_t__ parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  requestedPrivilegesW ; 
 int /*<<< orphan*/  securityW ; 
 scalar_t__ xml_elem_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xml_elem_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_security_elem(xmlbuf_t *xmlbuf, struct assembly *assembly, struct actctx_loader *acl)
{
    xmlstr_t elem;
    BOOL ret = TRUE;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xml_elem_cmp_end(&elem, securityW, asmv2W))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else if (xml_elem_cmp(&elem, requestedPrivilegesW, asmv2W))
            ret = parse_requested_privileges_elem(xmlbuf, assembly, acl);
        else
        {
            UNICODE_STRING elemU = xmlstr2unicode(&elem);
            DPRINT1("unknown elem %wZ\n", &elemU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    return ret;
}