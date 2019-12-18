#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct dll_redirect {void* name; void* hash; } ;
struct assembly {int dummy; } ;
struct actctx_loader {TYPE_1__* actctx; } ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_2__ {int /*<<< orphan*/  sections; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DLLREDIRECT_SECTION ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 struct dll_redirect* add_dll_redirect (struct assembly*) ; 
 int /*<<< orphan*/  asmv2W ; 
 int /*<<< orphan*/  comClassW ; 
 int /*<<< orphan*/  comInterfaceProxyStubW ; 
 int /*<<< orphan*/  fileW ; 
 int /*<<< orphan*/  g_nameW ; 
 int /*<<< orphan*/  hashW ; 
 int /*<<< orphan*/  hashalgW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_com_class_elem (int /*<<< orphan*/ *,struct dll_redirect*,struct actctx_loader*) ; 
 scalar_t__ parse_cominterface_proxy_stub_elem (int /*<<< orphan*/ *,struct dll_redirect*,struct actctx_loader*) ; 
 scalar_t__ parse_end_element (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_typelib_elem (int /*<<< orphan*/ *,struct dll_redirect*,struct actctx_loader*) ; 
 scalar_t__ parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_window_class_elem (int /*<<< orphan*/ *,struct dll_redirect*,struct actctx_loader*) ; 
 int /*<<< orphan*/  typelibW ; 
 int /*<<< orphan*/  windowClassW ; 
 scalar_t__ xml_elem_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstr_cmpi (int /*<<< orphan*/ *,char const*) ; 
 void* xmlstrdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_file_elem(xmlbuf_t* xmlbuf, struct assembly* assembly, struct actctx_loader* acl)
{
    xmlstr_t    attr_name, attr_value, elem;
    UNICODE_STRING attr_nameU, attr_valueU;
    BOOL        end = FALSE, error, ret = TRUE;
    struct dll_redirect* dll;

    if (!(dll = add_dll_redirect(assembly))) return FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        attr_nameU = xmlstr2unicode(&attr_name);
        attr_valueU = xmlstr2unicode(&attr_value);

        if (xmlstr_cmp(&attr_name, g_nameW))
        {
            if (!(dll->name = xmlstrdupW(&attr_value))) return FALSE;
            DPRINT("name=%wZ\n", &attr_valueU);
        }
        else if (xmlstr_cmp(&attr_name, hashW))
        {
            if (!(dll->hash = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, hashalgW))
        {
            static const WCHAR sha1W[] = {'S','H','A','1',0};
            if (!xmlstr_cmpi(&attr_value, sha1W))
                DPRINT1("hashalg should be SHA1, got %wZ\n", &attr_valueU);
        }
        else
        {
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error || !dll->name) return FALSE;

    acl->actctx->sections |= DLLREDIRECT_SECTION;

    if (end) return TRUE;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xmlstr_cmp_end(&elem, fileW))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else if (xmlstr_cmp(&elem, comClassW))
        {
            ret = parse_com_class_elem(xmlbuf, dll, acl);
        }
        else if (xmlstr_cmp(&elem, comInterfaceProxyStubW))
        {
            ret = parse_cominterface_proxy_stub_elem(xmlbuf, dll, acl);
        }
        else if (xml_elem_cmp(&elem, hashW, asmv2W))
        {
            DPRINT1("asmv2hash (undocumented) not supported\n");
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
        else if (xmlstr_cmp(&elem, typelibW))
        {
            ret = parse_typelib_elem(xmlbuf, dll, acl);
        }
        else if (xmlstr_cmp(&elem, windowClassW))
        {
            ret = parse_window_class_elem(xmlbuf, dll, acl);
        }
        else
        {
            attr_nameU = xmlstr2unicode(&elem);
            DPRINT1("unknown elem %wZ\n", &attr_nameU);
            ret = parse_unknown_elem( xmlbuf, &elem );
        }
    }

    return ret;
}