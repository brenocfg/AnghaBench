#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  psz_desc; int /*<<< orphan*/  psz_url; scalar_t__ i_revision; scalar_t__ i_minor; scalar_t__ i_major; } ;
struct TYPE_5__ {TYPE_1__ release; } ;
typedef  TYPE_2__ update_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EmptyRelease( update_t *p_update )
{
    p_update->release.i_major = 0;
    p_update->release.i_minor = 0;
    p_update->release.i_revision = 0;

    FREENULL( p_update->release.psz_url );
    FREENULL( p_update->release.psz_desc );
}