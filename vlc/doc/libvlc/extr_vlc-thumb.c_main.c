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
typedef  int /*<<< orphan*/  pthread_condattr_t ;
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
typedef  int /*<<< orphan*/  libvlc_instance_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdline (int,char const**,char const**,char**,char**,int*) ; 
 int /*<<< orphan*/ * create_libvlc () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * libvlc_media_new_path (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * libvlc_media_player_new_from_media (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_play (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_stop_async (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_condattr_setclock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  set_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snapshot (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  wait ; 

int main(int argc, const char **argv)
{
    const char *in;
    char *out, *out_with_ext;
    int width;
    pthread_condattr_t attr;
    libvlc_instance_t *libvlc;
    libvlc_media_player_t *mp;
    libvlc_media_t *m;

    /* mandatory to support UTF-8 filenames (provided the locale is well set)*/
    setlocale(LC_ALL, "");

    cmdline(argc, argv, &in, &out, &out_with_ext, &width);

    pthread_condattr_init(&attr);
    pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
    pthread_cond_init(&wait, &attr);
    pthread_condattr_destroy(&attr);

    /* starts vlc */
    libvlc = create_libvlc();
    assert(libvlc);

    m = libvlc_media_new_path(libvlc, in);
    assert(m);

    mp = libvlc_media_player_new_from_media(m);
    assert(mp);

    libvlc_media_player_play(mp);

    /* takes snapshot */
    set_position(mp);
    snapshot(mp, width, out_with_ext);

    libvlc_media_player_stop_async(mp);

    /* clean up */
    if (out != out_with_ext) {
        rename(out_with_ext, out);
        free(out_with_ext);
    }
    free(out);

    libvlc_media_player_release(mp);
    libvlc_media_release(m);
    libvlc_release(libvlc);

    pthread_cond_destroy(&wait);

    return 0;
}