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
struct vlc_gai_req {int /*<<< orphan*/  done; int /*<<< orphan*/  result; int /*<<< orphan*/  hints; int /*<<< orphan*/  service; int /*<<< orphan*/  name; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAI_SYSTEM ; 
 int /*<<< orphan*/  getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *vlc_gai_thread(void *data)
{
    struct vlc_gai_req *req = data;

    req->error = EAI_SYSTEM;
    req->error = getaddrinfo(req->name, req->service, req->hints,
                             &req->result);
    vlc_sem_post(&req->done);
    return NULL;
}