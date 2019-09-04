#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct assembly_identity {void* language; void* public_key; void* arch; int /*<<< orphan*/  version; void* type; void* name; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ACTIVATION_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  assemblyIdentityW ; 
 int /*<<< orphan*/  g_nameW ; 
 int /*<<< orphan*/  languageW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_version (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processorArchitectureW ; 
 int /*<<< orphan*/  publicKeyTokenW ; 
 int /*<<< orphan*/  typeW ; 
 int /*<<< orphan*/  versionW ; 
 int /*<<< orphan*/  xmlstr2unicode (TYPE_1__*) ; 
 scalar_t__ xmlstr_cmp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* xmlstrdupW (TYPE_1__*) ; 

__attribute__((used)) static BOOL parse_assembly_identity_elem(xmlbuf_t* xmlbuf, ACTIVATION_CONTEXT* actctx,
                                         struct assembly_identity* ai)
{
    xmlstr_t    attr_name, attr_value;
    BOOL        end = FALSE, error;
    UNICODE_STRING  attr_valueU, attr_nameU;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, g_nameW))
        {
            if (!(ai->name = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, typeW))
        {
            if (!(ai->type = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, versionW))
        {
            if (!parse_version(&attr_value, &ai->version)) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, processorArchitectureW))
        {
            if (!(ai->arch = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, publicKeyTokenW))
        {
            if (!(ai->public_key = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, languageW))
        {
            DPRINT("Unsupported yet language attribute (%.*S)\n",
                   attr_value.len, attr_value.ptr);
            if (!(ai->language = xmlstrdupW(&attr_value))) return FALSE;
        }
        else
        {
            attr_nameU = xmlstr2unicode(&attr_name);
            attr_valueU = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error || end) return end;
    return parse_expect_end_elem(xmlbuf, assemblyIdentityW, asmv1W);
}