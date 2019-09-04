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
struct inf_section {int dummy; } ;
struct ciffile {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  process_component (struct ciffile*,struct inf_section*,char const*) ; 
 int /*<<< orphan*/  process_group (struct ciffile*,struct inf_section*,char const*) ; 
 int /*<<< orphan*/  section_get_str (struct inf_section*,char*,char**,char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static HRESULT process_section(struct ciffile *file, struct inf_section *section, const char *section_name)
{
    HRESULT hr;
    char *type;

    if (!section_get_str(section, "SectionType", &type, "Component"))
        return E_OUTOFMEMORY;

    if (!strcasecmp(type, "Component"))
        hr = process_component(file, section, section_name);
    else if (strcasecmp(type, "Group") == 0)
        hr = process_group(file, section, section_name);
    else
        FIXME("Don't know how to process %s\n", debugstr_a(type));

    heap_free(type);
    return hr;
}