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
typedef  int /*<<< orphan*/  services_discovery_t ;
typedef  int /*<<< orphan*/  netbios_ns_entry ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  ITEM_NET ; 
 char NETBIOS_FILESERVER ; 
 scalar_t__ asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  entry_item_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * input_item_NewDirectory (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 char* netbios_ns_entry_name (int /*<<< orphan*/ *) ; 
 char netbios_ns_entry_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netbios_ns_discover_on_entry_added( void *p_opaque,
                                                netbios_ns_entry *p_entry )
{
    services_discovery_t *p_sd = (services_discovery_t *)p_opaque;

    char type = netbios_ns_entry_type( p_entry );

    if( type == NETBIOS_FILESERVER )
    {
        input_item_t *p_item;
        char *psz_mrl;
        const char *name = netbios_ns_entry_name( p_entry );

        if( asprintf(&psz_mrl, "smb://%s", name) < 0 )
            return;

        p_item = input_item_NewDirectory( psz_mrl, name, ITEM_NET );
        msg_Dbg( p_sd, "Adding item %s", psz_mrl );
        free(psz_mrl);

        entry_item_append( p_sd, p_entry, p_item );
        input_item_Release( p_item );
    }
}