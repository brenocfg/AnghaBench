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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int libvlc_media_player_get_role (int /*<<< orphan*/ *) ; 
 scalar_t__ libvlc_media_player_set_role (int /*<<< orphan*/ *,int) ; 
 int libvlc_role_Last ; 
 int libvlc_role_Video ; 

__attribute__((used)) static void test_role(libvlc_media_player_t *mp)
{
    int role;

    /* Test default value */
    assert(libvlc_media_player_get_role(mp) == libvlc_role_Video);

    for (role = 0; libvlc_media_player_set_role(mp, role) == 0; role++)
        assert(libvlc_media_player_get_role(mp) == role);

    assert(role > libvlc_role_Last);
}