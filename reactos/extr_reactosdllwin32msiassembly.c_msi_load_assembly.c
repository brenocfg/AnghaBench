#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_22__ {char* attributes; void* installed; void** clr_version; struct TYPE_22__* display_name; struct TYPE_22__* application; struct TYPE_22__* manifest; struct TYPE_22__* feature; } ;
struct TYPE_21__ {int /*<<< orphan*/  Component; } ;
struct TYPE_20__ {int /*<<< orphan*/ * cache_net; int /*<<< orphan*/  cache_sxs; int /*<<< orphan*/  db; } ;
struct TYPE_19__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ MSIRECORD ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  TYPE_3__ MSICOMPONENT ;
typedef  TYPE_4__ MSIASSEMBLY ;

/* Variables and functions */
 size_t CLR_VERSION_MAX ; 
 void* FALSE ; 
 char* MSI_RecordGetInteger (TYPE_1__*,int) ; 
 int /*<<< orphan*/  MSI_RecordGetString (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 char* debugstr_w (TYPE_4__*) ; 
 TYPE_4__* get_assembly_display_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_1__* get_assembly_record (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* get_clr_version_str (size_t) ; 
 void* is_assembly_installed (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_4__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_4__*) ; 
 scalar_t__ msidbAssemblyAttributesWin32 ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 void* strdupW (int /*<<< orphan*/ ) ; 

MSIASSEMBLY *msi_load_assembly( MSIPACKAGE *package, MSICOMPONENT *comp )
{
    MSIRECORD *rec;
    MSIASSEMBLY *a;

    if (!(rec = get_assembly_record( package, comp->Component ))) return NULL;
    if (!(a = msi_alloc_zero( sizeof(MSIASSEMBLY) )))
    {
        msiobj_release( &rec->hdr );
        return NULL;
    }
    a->feature = strdupW( MSI_RecordGetString( rec, 2 ) );
    TRACE("feature %s\n", debugstr_w(a->feature));

    a->manifest = strdupW( MSI_RecordGetString( rec, 3 ) );
    TRACE("manifest %s\n", debugstr_w(a->manifest));

    a->application = strdupW( MSI_RecordGetString( rec, 4 ) );
    TRACE("application %s\n", debugstr_w(a->application));

    a->attributes = MSI_RecordGetInteger( rec, 5 );
    TRACE("attributes %u\n", a->attributes);

    if (!(a->display_name = get_assembly_display_name( package->db, comp->Component, a )))
    {
        WARN("can't get display name\n");
        msiobj_release( &rec->hdr );
        msi_free( a->feature );
        msi_free( a->manifest );
        msi_free( a->application );
        msi_free( a );
        return NULL;
    }
    TRACE("display name %s\n", debugstr_w(a->display_name));

    if (a->application)
    {
        /* We can't check the manifest here because the target path may still change.
           So we assume that the assembly is not installed and lean on the InstallFiles
           action to determine which files need to be installed.
         */
        a->installed = FALSE;
    }
    else
    {
        if (a->attributes == msidbAssemblyAttributesWin32)
            a->installed = is_assembly_installed( package->cache_sxs, a->display_name );
        else
        {
            UINT i;
            for (i = 0; i < CLR_VERSION_MAX; i++)
            {
                a->clr_version[i] = is_assembly_installed( package->cache_net[i], a->display_name );
                if (a->clr_version[i])
                {
                    TRACE("runtime version %s\n", debugstr_w(get_clr_version_str( i )));
                    a->installed = TRUE;
                    break;
                }
            }
        }
    }
    TRACE("assembly is %s\n", a->installed ? "installed" : "not installed");
    msiobj_release( &rec->hdr );
    return a;
}