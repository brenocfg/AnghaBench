#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* tempdir; struct TYPE_5__* display_name; struct TYPE_5__* application; struct TYPE_5__* manifest; struct TYPE_5__* feature; } ;
typedef  TYPE_1__ MSIASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveDirectoryW (TYPE_1__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

__attribute__((used)) static void free_assembly( MSIASSEMBLY *assembly )
{
    msi_free( assembly->feature );
    msi_free( assembly->manifest );
    msi_free( assembly->application );
    msi_free( assembly->display_name );
    if (assembly->tempdir) RemoveDirectoryW( assembly->tempdir );
    msi_free( assembly->tempdir );
    msi_free( assembly );
}