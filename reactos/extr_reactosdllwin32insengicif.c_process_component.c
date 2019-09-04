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
struct inf_section {int dummy; } ;
struct ciffile {int /*<<< orphan*/  ICifFile_iface; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct cifcomponent {int /*<<< orphan*/  priority; int /*<<< orphan*/  current_priority; int /*<<< orphan*/  platform; int /*<<< orphan*/  build; int /*<<< orphan*/  version; int /*<<< orphan*/  as_aware; int /*<<< orphan*/  visibleui; int /*<<< orphan*/  admin; int /*<<< orphan*/  reboot; int /*<<< orphan*/  key_uninstall; int /*<<< orphan*/  key_progress; int /*<<< orphan*/  key_cancel; int /*<<< orphan*/  key_success; int /*<<< orphan*/  size_win; int /*<<< orphan*/  size_app; int /*<<< orphan*/  size_extracted; int /*<<< orphan*/  size_download; int /*<<< orphan*/  patchid; int /*<<< orphan*/  locale; int /*<<< orphan*/  group; int /*<<< orphan*/  details; int /*<<< orphan*/  guid; int /*<<< orphan*/  description; int /*<<< orphan*/  id; int /*<<< orphan*/  queue_state; int /*<<< orphan*/  dependencies; int /*<<< orphan*/  urls; int /*<<< orphan*/ * parent; TYPE_1__ ICifComponent_iface; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ActionNone ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  add_component_by_priority (struct ciffile*,struct cifcomponent*) ; 
 int /*<<< orphan*/  cifcomponentVtbl ; 
 int /*<<< orphan*/  component_free (struct cifcomponent*) ; 
 struct cifcomponent* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_dependencies (struct cifcomponent*,struct inf_section*) ; 
 int /*<<< orphan*/  read_platform_entry (struct inf_section*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_urls (struct cifcomponent*,struct inf_section*) ; 
 int /*<<< orphan*/  read_version_entry (struct inf_section*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  section_get_dword (struct inf_section*,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  section_get_dword_field (struct inf_section*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  section_get_str (struct inf_section*,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdupA (char const*) ; 

__attribute__((used)) static HRESULT process_component(struct ciffile *file, struct inf_section *section, const char *section_name)
{
    struct cifcomponent *component;
    HRESULT hr = E_OUTOFMEMORY;

    component = heap_alloc_zero(sizeof(*component));
    if (!component) return E_OUTOFMEMORY;

    component->ICifComponent_iface.lpVtbl = &cifcomponentVtbl;
    component->parent = &file->ICifFile_iface;

    list_init(&component->urls);
    list_init(&component->dependencies);

    component->queue_state = ActionNone;

    component->id = strdupA(section_name);
    if (!component->id) goto error;

    if (!section_get_str(section, "DisplayName", &component->description, NULL))
        goto error;
    if (!section_get_str(section, "GUID", &component->guid, NULL))
        goto error;
    if (!section_get_str(section, "Details", &component->details, NULL))
        goto error;
    if (!section_get_str(section, "Group", &component->group, NULL))
        goto error;
    if (!section_get_str(section, "Locale", &component->locale, "en"))
        goto error;
    if (!section_get_str(section, "PatchID", &component->patchid, NULL))
        goto error;

    if (!section_get_dword_field(section, "Size", 1, &component->size_download, 0))
        goto error;
    if (!section_get_dword_field(section, "Size", 2, &component->size_extracted, 0))
        goto error;
    if (!section_get_dword_field(section, "InstalledSize", 1, &component->size_app, 0))
        goto error;
    if (!section_get_dword_field(section, "InstalledSize", 2, &component->size_win, 0))
        goto error;

    if (!section_get_str(section, "SuccessKey", &component->key_success, NULL))
        goto error;
    if (!section_get_str(section, "CancelKey", &component->key_cancel, NULL))
        goto error;
    if (!section_get_str(section, "ProgressKey", &component->key_progress, NULL))
        goto error;
    if (!section_get_str(section, "UninstallKey", &component->key_uninstall, NULL))
        goto error;
    if (!section_get_dword(section, "Reboot", &component->reboot, 0))
        goto error;
    if (!section_get_dword(section, "AdminCheck", &component->admin, 0))
        goto error;
    if (!section_get_dword(section, "UIVisible", &component->visibleui, 1))
        goto error;
    if (!section_get_dword(section, "ActiveSetupAware", &component->as_aware, 0))
        goto error;
    if (!section_get_dword(section, "Priority", &component->priority, 0))
        goto error;

    if (!read_version_entry(section, &component->version, &component->build))
        goto error;
    if (!read_platform_entry(section, &component->platform))
        goto error;
    if (!read_urls(component, section))
        goto error;
    if (!read_dependencies(component, section))
        goto error;

    component->current_priority = component->priority;

    add_component_by_priority(file, component);
    return S_OK;

error:
    component_free(component);
    return hr;
}