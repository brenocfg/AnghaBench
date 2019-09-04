#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct reader_position {int dummy; } ;
struct TYPE_11__ {struct reader_position position; } ;
struct TYPE_12__ {TYPE_1__ empty_element; int /*<<< orphan*/  nodetype; struct reader_position position; } ;
typedef  TYPE_2__ xmlreader ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringValue_LocalName ; 
 int /*<<< orphan*/  StringValue_QualifiedName ; 
 int /*<<< orphan*/  WC_E_XMLDECL ; 
 int /*<<< orphan*/  XmlNodeType_XmlDeclaration ; 
 scalar_t__ reader_cmp (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  reader_parse_encdecl (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_sddecl (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_parse_versioninfo (TYPE_2__*) ; 
 int /*<<< orphan*/  reader_set_strvalue (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (TYPE_2__*,int) ; 
 int /*<<< orphan*/  reader_skipspaces (TYPE_2__*) ; 
 int /*<<< orphan*/  strval_xml ; 

__attribute__((used)) static HRESULT reader_parse_xmldecl(xmlreader *reader)
{
    static const WCHAR xmldeclW[] = {'<','?','x','m','l',' ',0};
    static const WCHAR declcloseW[] = {'?','>',0};
    struct reader_position position;
    HRESULT hr;

    /* check if we have "<?xml " */
    if (reader_cmp(reader, xmldeclW))
        return S_FALSE;

    reader_skipn(reader, 2);
    position = reader->position;
    reader_skipn(reader, 3);
    hr = reader_parse_versioninfo(reader);
    if (FAILED(hr))
        return hr;

    hr = reader_parse_encdecl(reader);
    if (FAILED(hr))
        return hr;

    hr = reader_parse_sddecl(reader);
    if (FAILED(hr))
        return hr;

    reader_skipspaces(reader);
    if (reader_cmp(reader, declcloseW))
        return WC_E_XMLDECL;

    /* skip '?>' */
    reader_skipn(reader, 2);

    reader->nodetype = XmlNodeType_XmlDeclaration;
    reader->empty_element.position = position;
    reader_set_strvalue(reader, StringValue_LocalName, &strval_xml);
    reader_set_strvalue(reader, StringValue_QualifiedName, &strval_xml);

    return S_OK;
}