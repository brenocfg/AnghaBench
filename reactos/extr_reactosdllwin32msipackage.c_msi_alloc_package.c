#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cabinet_streams; int /*<<< orphan*/  binaries; int /*<<< orphan*/  patches; int /*<<< orphan*/  sourcelist_media; int /*<<< orphan*/  sourcelist_info; int /*<<< orphan*/  RunningActions; int /*<<< orphan*/  progids; int /*<<< orphan*/  extensions; int /*<<< orphan*/  mimes; int /*<<< orphan*/  classes; int /*<<< orphan*/  appids; int /*<<< orphan*/  subscriptions; int /*<<< orphan*/  folders; int /*<<< orphan*/  tempfiles; int /*<<< orphan*/  filepatches; int /*<<< orphan*/  files; int /*<<< orphan*/  features; int /*<<< orphan*/  components; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 int /*<<< orphan*/  MSIHANDLETYPE_PACKAGE ; 
 int /*<<< orphan*/  MSI_FreePackage ; 
 TYPE_1__* alloc_msiobject (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MSIPACKAGE *msi_alloc_package( void )
{
    MSIPACKAGE *package;

    package = alloc_msiobject( MSIHANDLETYPE_PACKAGE, sizeof (MSIPACKAGE),
                               MSI_FreePackage );
    if( package )
    {
        list_init( &package->components );
        list_init( &package->features );
        list_init( &package->files );
        list_init( &package->filepatches );
        list_init( &package->tempfiles );
        list_init( &package->folders );
        list_init( &package->subscriptions );
        list_init( &package->appids );
        list_init( &package->classes );
        list_init( &package->mimes );
        list_init( &package->extensions );
        list_init( &package->progids );
        list_init( &package->RunningActions );
        list_init( &package->sourcelist_info );
        list_init( &package->sourcelist_media );
        list_init( &package->patches );
        list_init( &package->binaries );
        list_init( &package->cabinet_streams );
    }

    return package;
}