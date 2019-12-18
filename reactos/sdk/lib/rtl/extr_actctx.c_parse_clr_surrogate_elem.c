#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlstr_t ;
typedef  int /*<<< orphan*/  xmlbuf_t ;
struct TYPE_4__ {void* version; void* clsid; void* name; } ;
struct TYPE_5__ {TYPE_1__ clrsurrogate; } ;
struct entity {TYPE_2__ u; } ;
struct assembly {int /*<<< orphan*/  entities; } ;
struct actctx_loader {TYPE_3__* actctx; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_6__ {int /*<<< orphan*/  sections; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES ; 
 int /*<<< orphan*/  CLRSURROGATES_SECTION ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 struct entity* add_entity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asmv1W ; 
 int /*<<< orphan*/  clrSurrogateW ; 
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  g_nameW ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 scalar_t__ parse_expect_end_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runtimeVersionW ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* xmlstrdupW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL parse_clr_surrogate_elem(xmlbuf_t* xmlbuf, struct assembly* assembly, struct actctx_loader *acl)
{
    xmlstr_t    attr_name, attr_value;
    UNICODE_STRING attr_nameU, attr_valueU;
    BOOL        end = FALSE, error;
    struct entity*      entity;

    entity = add_entity(&assembly->entities, ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES);
    if (!entity) return FALSE;

    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, g_nameW))
        {
            if (!(entity->u.clrsurrogate.name = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, clsidW))
        {
            if (!(entity->u.clrsurrogate.clsid = xmlstrdupW(&attr_value))) return FALSE;
        }
        else if (xmlstr_cmp(&attr_name, runtimeVersionW))
        {
            if (!(entity->u.clrsurrogate.version = xmlstrdupW(&attr_value))) return FALSE;
        }
        else
        {
            attr_nameU = xmlstr2unicode(&attr_name);
            attr_valueU = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error) return FALSE;
    acl->actctx->sections |= CLRSURROGATES_SECTION;
    if (end) return TRUE;

    return parse_expect_end_elem(xmlbuf, clrSurrogateW, asmv1W);
}