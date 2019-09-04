#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  localfile; scalar_t__ delete_on_close; int /*<<< orphan*/  log_file; TYPE_1__* db; scalar_t__ dialog; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_2__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  MSIOBJECTHDR ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTALLMESSAGE_TERMINATE ; 
 int /*<<< orphan*/  MSI_ProcessMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_package_structures (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_destroy_assembly_caches (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_dialog_destroy (scalar_t__) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MSI_FreePackage( MSIOBJECTHDR *arg)
{
    MSIPACKAGE *package = (MSIPACKAGE *)arg;

    msi_destroy_assembly_caches( package );

    if( package->dialog )
        msi_dialog_destroy( package->dialog );

    msiobj_release( &package->db->hdr );
    free_package_structures(package);
    CloseHandle( package->log_file );

    if (package->delete_on_close) DeleteFileW( package->localfile );
    msi_free( package->localfile );
    MSI_ProcessMessage(NULL, INSTALLMESSAGE_TERMINATE, 0);
}