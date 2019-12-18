#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* psz_username; int /*<<< orphan*/ * psz_password; } ;
typedef  TYPE_1__ vlc_credential ;

/* Variables and functions */

__attribute__((used)) static bool
is_credential_valid(vlc_credential *p_credential)
{
    if (p_credential->psz_username && *p_credential->psz_username != '\0'
     && p_credential->psz_password)
        return true;
    p_credential->psz_password = NULL;
    return false;
}