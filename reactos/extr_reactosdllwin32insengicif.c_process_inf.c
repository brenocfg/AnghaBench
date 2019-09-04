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
struct inf_file {int dummy; } ;
struct ciffile {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_INSTALLER_DESC ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 scalar_t__ inf_next_section (struct inf_file*,struct inf_section**) ; 
 char* inf_section_get_name (struct inf_section*) ; 
 int /*<<< orphan*/  process_section (struct ciffile*,struct inf_section*,char*) ; 
 int /*<<< orphan*/  process_version (struct ciffile*,struct inf_section*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strdupA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT process_inf(struct ciffile *file, struct inf_file *inf)
{
    struct inf_section *section = NULL;
    char *section_name;
    HRESULT hr = S_OK;

    while (SUCCEEDED(hr) && inf_next_section(inf, &section))
    {
        section_name = inf_section_get_name(section);
        if (!section_name) return E_OUTOFMEMORY;

        TRACE("start processing section %s\n", debugstr_a(section_name));

        if (!strcasecmp(section_name, "Strings") ||
            !strncasecmp(section_name, "Strings.", strlen("Strings.")))
        {
            /* Ignore string sections */
        }
        else if (strcasecmp(section_name, "Version") == 0)
            hr = process_version(file, section);
        else
            hr = process_section(file, section, section_name);

        TRACE("finished processing section %s (%x)\n", debugstr_a(section_name), hr);
        heap_free(section_name);
    }

    /* In case there was no version section, set the default installer description */
    if (SUCCEEDED(hr) && !file->name)
    {
        file->name = strdupA(DEFAULT_INSTALLER_DESC);
        if (!file->name) hr = E_OUTOFMEMORY;
    }

    return hr;
}