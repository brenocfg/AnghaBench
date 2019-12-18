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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  bindingRedirectW ; 
 int /*<<< orphan*/  newVersionW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  oldVersionW ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL parse_binding_redirect_elem(xmlbuf_t* xmlbuf)
{
    xmlstr_t    attr_name, attr_value;
    UNICODE_STRING  attr_valueU, attr_nameU;
    BOOL        end = FALSE, error;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        attr_nameU = xmlstr2unicode(&attr_name);
        attr_valueU = xmlstr2unicode(&attr_value);

        if (xmlstr_cmp(&attr_name, oldVersionW))
        {
            DPRINT1("Not stored yet oldVersion=%wZ\n", &attr_valueU);
        }
        else if (xmlstr_cmp(&attr_name, newVersionW))
        {
            DPRINT1("Not stored yet newVersion=%wZ\n", &attr_valueU);
        }
        else
        {
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error || end) return end;
    return parse_expect_end_elem(xmlbuf, bindingRedirectW, asmv1W);
}