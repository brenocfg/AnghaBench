#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_instance_t ;
struct TYPE_7__ {char* psz_name; char* psz_description; struct TYPE_7__* p_next; } ;
typedef  TYPE_1__ libvlc_audio_output_t ;
struct TYPE_8__ {char* psz_device; char* psz_description; struct TYPE_8__* p_next; } ;
typedef  TYPE_2__ libvlc_audio_output_device_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* libvlc_audio_output_device_list_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  libvlc_audio_output_device_list_release (TYPE_2__*) ; 
 TYPE_1__* libvlc_audio_output_list_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_audio_output_list_release (TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void test_audio_output (void)
{
    libvlc_instance_t *vlc = libvlc_new (0, NULL);
    assert (vlc != NULL);

    libvlc_audio_output_t *mods = libvlc_audio_output_list_get (vlc);
    assert (mods != NULL);

    puts ("Audio outputs:");
    for (const libvlc_audio_output_t *o = mods; o != NULL; o = o->p_next)
    {
        libvlc_audio_output_device_t *devs;

        printf(" %s: %s\n", o->psz_name, o->psz_description);

        devs = libvlc_audio_output_device_list_get (vlc, o->psz_name);
        if (devs == NULL)
            continue;
        for (const libvlc_audio_output_device_t *d = devs;
             d != NULL;
             d = d->p_next)
             printf("  %s: %s\n", d->psz_device, d->psz_description);

        libvlc_audio_output_device_list_release (devs);
    }
    libvlc_audio_output_list_release (mods);
    libvlc_release (vlc);
}