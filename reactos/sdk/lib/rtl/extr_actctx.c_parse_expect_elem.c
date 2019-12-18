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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ xml_elem_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_expect_elem(xmlbuf_t* xmlbuf, const WCHAR* name, const WCHAR *namespace)
{
    xmlstr_t    elem;
    UNICODE_STRING elemU;
    if (!next_xml_elem(xmlbuf, &elem)) return FALSE;
    if (xml_elem_cmp(&elem, name, namespace)) return TRUE;
    elemU = xmlstr2unicode(&elem);
    DPRINT1( "unexpected element %wZ\n", &elemU );
    return FALSE;
}