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
struct TYPE_4__ {int /*<<< orphan*/  name; void* versioned; } ;
struct TYPE_5__ {TYPE_1__ class; } ;
struct entity {TYPE_2__ u; } ;
struct dll_redirect {int /*<<< orphan*/  entities; } ;
struct actctx_loader {TYPE_3__* actctx; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_6__ {int /*<<< orphan*/  sections; } ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ *,...) ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  WINDOWCLASS_SECTION ; 
 struct entity* add_entity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ next_xml_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,void**) ; 
 void* next_xml_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noW ; 
 void* parse_end_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_text_content (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* parse_unknown_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  versionedW ; 
 int /*<<< orphan*/  windowClassW ; 
 int /*<<< orphan*/  xmlstr2unicode (int /*<<< orphan*/ *) ; 
 scalar_t__ xmlstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmp_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xmlstr_cmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlstrdupW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yesW ; 

__attribute__((used)) static BOOL parse_window_class_elem(xmlbuf_t* xmlbuf, struct dll_redirect* dll, struct actctx_loader* acl)
{
    xmlstr_t elem, content, attr_name, attr_value;
    BOOL end = FALSE, ret = TRUE, error;
    struct entity*      entity;
    UNICODE_STRING elemU, attr_nameU, attr_valueU;

    if (!(entity = add_entity(&dll->entities, ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION)))
        return FALSE;

    entity->u.class.versioned = TRUE;
    while (next_xml_attr(xmlbuf, &attr_name, &attr_value, &error, &end))
    {
        if (xmlstr_cmp(&attr_name, versionedW))
        {
            if (xmlstr_cmpi(&attr_value, noW))
                entity->u.class.versioned = FALSE;
            else if (!xmlstr_cmpi(&attr_value, yesW))
               return FALSE;
        }
        else
        {
            attr_nameU = xmlstr2unicode(&attr_name);
            attr_valueU = xmlstr2unicode(&attr_value);
            DPRINT1("unknown attr %wZ=%wZ\n", &attr_nameU, &attr_valueU);
        }
    }

    if (error || end) return end;

    if (!parse_text_content(xmlbuf, &content)) return FALSE;

    if (!(entity->u.class.name = xmlstrdupW(&content))) return FALSE;

    acl->actctx->sections |= WINDOWCLASS_SECTION;

    while (ret && (ret = next_xml_elem(xmlbuf, &elem)))
    {
        if (xmlstr_cmp_end(&elem, windowClassW))
        {
            ret = parse_end_element(xmlbuf);
            break;
        }
        else
        {
            elemU = xmlstr2unicode(&elem);
            DPRINT1("unknown elem %wZ\n", &elemU);
            ret = parse_unknown_elem(xmlbuf, &elem);
        }
    }

    return ret;
}