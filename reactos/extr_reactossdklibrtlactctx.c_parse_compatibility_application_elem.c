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
 int /*<<< orphan*/  applicationW ; 
 scalar_t__ next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_supportedos_elem (int /*<<< orphan*/ *,struct assembly*,struct actctx_loader*) ; 
 scalar_t__ parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supportedOSW ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_compatibility_application_elem(xmlbuf_t* xmlbuf, struct assembly* assembly,
                                                 struct actctx_loader* acl)
{
    BOOL ret = TRUE;
    xmlstr_t elem;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xmlstr_cmp_end(&elem, applicationW))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else if (xmlstr_cmp(&elem, supportedOSW))
        {
            ret = parse_supportedos_elem(xmlbuf, assembly, acl);
        }
        else
        {
            UNICODE_STRING elemU = xmlstr2unicode(&elem);
            DPRINT1("unknown elem %wZ\n", &elemU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    return ret;
}