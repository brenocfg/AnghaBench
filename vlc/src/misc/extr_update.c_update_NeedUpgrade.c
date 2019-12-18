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
struct TYPE_5__ {int const i_major; int const i_minor; int const i_revision; int const i_extra; } ;
struct TYPE_6__ {TYPE_1__ release; } ;
typedef  TYPE_2__ update_t ;

/* Variables and functions */
 scalar_t__* PACKAGE_VERSION_DEV ; 
#define  PACKAGE_VERSION_EXTRA 131 
#define  PACKAGE_VERSION_MAJOR 130 
#define  PACKAGE_VERSION_MINOR 129 
#define  PACKAGE_VERSION_REVISION 128 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

bool update_NeedUpgrade( update_t *p_update )
{
    assert( p_update );

    static const int current[4] = {
        PACKAGE_VERSION_MAJOR,
        PACKAGE_VERSION_MINOR,
        PACKAGE_VERSION_REVISION,
        PACKAGE_VERSION_EXTRA
    };
    const int latest[4] = {
        p_update->release.i_major,
        p_update->release.i_minor,
        p_update->release.i_revision,
        p_update->release.i_extra
    };

    for (unsigned i = 0; i < sizeof latest / sizeof *latest; i++) {
        /* there is a new version available */
        if (latest[i] > current[i])
            return true;

        /* current version is more recent than the latest version ?! */
        if (latest[i] < current[i])
            return false;
    }

    /* current version is not a release, it's a -git or -rc version */
    if (*PACKAGE_VERSION_DEV)
        return true;

    /* current version is latest version */
    return false;
}