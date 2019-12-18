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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_2__ {char const* psz_role; char const* psz_name; } ;
typedef  char OMX_U8 ;
typedef  int OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;

/* Variables and functions */
 unsigned int MAX_COMPONENTS_LIST_SIZE ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int OMX_MAX_STRINGNAME_SIZE ; 
 int /*<<< orphan*/  free (char**) ; 
 char** malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  pf_component_enum (char*,int,unsigned int) ; 
 int /*<<< orphan*/  pf_get_roles_of_component (char*,int*,char**) ; 
 TYPE_1__* role_mappings ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int CreateComponentsList(vlc_object_t *p_this, const char *psz_role,
                         char ppsz_components[MAX_COMPONENTS_LIST_SIZE][OMX_MAX_STRINGNAME_SIZE])
{
    char psz_name[OMX_MAX_STRINGNAME_SIZE];
    OMX_ERRORTYPE omx_error;
    OMX_U32 roles = 0;
    OMX_U8 **ppsz_roles = 0;
    unsigned int i, j, components = 0;

    if(!psz_role) goto end;

    for( i = 0; ; i++ )
    {
        bool b_found = false;

        omx_error = pf_component_enum(psz_name, OMX_MAX_STRINGNAME_SIZE, i);
        if(omx_error != OMX_ErrorNone) break;

        msg_Dbg(p_this, "component %s", psz_name);

        for( unsigned int j = 0; role_mappings[j].psz_role; j++ ) {
            if( !strcmp( psz_role, role_mappings[j].psz_role ) &&
                !strcmp( psz_name, role_mappings[j].psz_name ) ) {
                goto found;
            }
        }

        omx_error = pf_get_roles_of_component(psz_name, &roles, 0);
        if(omx_error != OMX_ErrorNone || !roles) continue;

        ppsz_roles = malloc(roles * (sizeof(OMX_U8*) + OMX_MAX_STRINGNAME_SIZE));
        if(!ppsz_roles) continue;

        for( j = 0; j < roles; j++ )
            ppsz_roles[j] = ((OMX_U8 *)(&ppsz_roles[roles])) +
                j * OMX_MAX_STRINGNAME_SIZE;

        omx_error = pf_get_roles_of_component(psz_name, &roles, ppsz_roles);
        if(omx_error != OMX_ErrorNone) roles = 0;

        for(j = 0; j < roles; j++)
        {
            msg_Dbg(p_this, "  - role: %s", ppsz_roles[j]);
            if(!strcmp((char *)ppsz_roles[j], psz_role)) b_found = true;
        }

        free(ppsz_roles);

        if(!b_found) continue;

found:
        if(components >= MAX_COMPONENTS_LIST_SIZE)
        {
            msg_Dbg(p_this, "too many matching components");
            continue;
        }

        strncpy(ppsz_components[components], psz_name,
                OMX_MAX_STRINGNAME_SIZE-1);
        components++;
    }

 end:
    msg_Dbg(p_this, "found %i matching components for role %s",
            components, psz_role);
    for( i = 0; i < components; i++ )
        msg_Dbg(p_this, "- %s", ppsz_components[i]);

    return components;
}