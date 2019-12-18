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
struct pollfd {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_t ;

/* Variables and functions */
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  snd_pcm_poll_descriptors (int /*<<< orphan*/ *,struct pollfd*,int) ; 
 int snd_pcm_poll_descriptors_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_poll_descriptors_revents (int /*<<< orphan*/ *,struct pollfd*,int,unsigned short*) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static void Poll (snd_pcm_t *pcm, int canc)
{
    int n = snd_pcm_poll_descriptors_count (pcm);
    struct pollfd ufd[n];
    unsigned short revents;

    snd_pcm_poll_descriptors (pcm, ufd, n);
    do
    {
        vlc_restorecancel (canc);
        while (poll (ufd, n, -1) == -1);
        canc = vlc_savecancel ();
        snd_pcm_poll_descriptors_revents (pcm, ufd, n, &revents);
    }
    while (!revents);
}