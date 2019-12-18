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
typedef  int /*<<< orphan*/  vlc_thread_t ;
struct vlc_gai_req {char const* name; char* service; int error; struct addrinfo* result; int /*<<< orphan*/  done; struct addrinfo const* hints; } ;
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  portbuf ;

/* Variables and functions */
 int EAI_NONAME ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 scalar_t__ snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vlc_gai_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_gai_thread ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_wait_i11e (int /*<<< orphan*/ *) ; 

int vlc_getaddrinfo_i11e(const char *name, unsigned port,
                         const struct addrinfo *hints,
                         struct addrinfo **res)
{
    struct vlc_gai_req req =
    {
        .name = name,
        .service = NULL,
        .hints = hints,
    };
    char portbuf[6];
    vlc_thread_t th;

    if (port != 0)
    {
        if ((size_t)snprintf(portbuf, sizeof (portbuf), "%u",
                             port) >= sizeof (portbuf))
            return EAI_NONAME;

        req.service = portbuf;
    }

    vlc_sem_init(&req.done, 0);

    if (vlc_clone(&th, vlc_gai_thread, &req, VLC_THREAD_PRIORITY_LOW))
    {
        vlc_sem_destroy(&req.done);
        return EAI_SYSTEM;
    }

    vlc_sem_wait_i11e(&req.done);

    vlc_cancel(th);
    vlc_join(th, NULL);
    vlc_sem_destroy(&req.done);

    *res = req.result;
    return req.error;
}