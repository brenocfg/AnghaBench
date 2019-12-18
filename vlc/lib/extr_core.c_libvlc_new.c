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
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_5__ {int ref_count; int /*<<< orphan*/  instance_lock; int /*<<< orphan*/ * p_callback_list; int /*<<< orphan*/ * p_libvlc_int; } ;
typedef  TYPE_1__ libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_InternalCreate () ; 
 int /*<<< orphan*/  libvlc_InternalDestroy (int /*<<< orphan*/ *) ; 
 scalar_t__ libvlc_InternalInit (int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/  libvlc_threads_deinit () ; 
 int /*<<< orphan*/  libvlc_threads_init () ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

libvlc_instance_t * libvlc_new( int argc, const char *const *argv )
{
    libvlc_threads_init ();

    libvlc_instance_t *p_new = malloc (sizeof (*p_new));
    if (unlikely(p_new == NULL))
        return NULL;

    const char *my_argv[argc + 2];
    my_argv[0] = "libvlc"; /* dummy arg0, skipped by getopt() et al */
    for( int i = 0; i < argc; i++ )
         my_argv[i + 1] = argv[i];
    my_argv[argc + 1] = NULL; /* C calling conventions require a NULL */

    libvlc_int_t *p_libvlc_int = libvlc_InternalCreate();
    if (unlikely (p_libvlc_int == NULL))
        goto error;

    if (libvlc_InternalInit( p_libvlc_int, argc + 1, my_argv ))
    {
        libvlc_InternalDestroy( p_libvlc_int );
        goto error;
    }

    p_new->p_libvlc_int = p_libvlc_int;
    p_new->ref_count = 1;
    p_new->p_callback_list = NULL;
    vlc_mutex_init(&p_new->instance_lock);
    return p_new;

error:
    free (p_new);
    libvlc_threads_deinit ();
    return NULL;
}