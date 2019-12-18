#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ptr; int len; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int*,int*) ; 
 int next_xml_elem (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmpW (char*,char*,int) ; 

__attribute__((used)) static BOOL parse_unknown_elem(xmlbuf_t *xmlbuf, const xmlstr_t *unknown_elem)
{
    xmlstr_t attr_name, attr_value, elem;
    BOOL end = FALSE, error, ret = TRUE;

    while(next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end));
    if(error || end) return end;

    while(ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if(*elem.ptr == '/' && elem.len - 1 == unknown_elem->len &&
           !strncmpW(elem.ptr+1, unknown_elem->ptr, unknown_elem->len))
            break;
        else
            ret = parse_unknown_elem(xmlbuf, &elem);
    }

    return ret && parse_end_element(xmlbuf);
}