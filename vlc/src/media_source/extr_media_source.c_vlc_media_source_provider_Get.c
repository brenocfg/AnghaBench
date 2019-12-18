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
typedef  int /*<<< orphan*/  vlc_media_source_provider_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_2__ {int /*<<< orphan*/ * media_source_provider; } ;

/* Variables and functions */
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 

vlc_media_source_provider_t *
vlc_media_source_provider_Get(libvlc_int_t *libvlc)
{
    return libvlc_priv(libvlc)->media_source_provider;
}