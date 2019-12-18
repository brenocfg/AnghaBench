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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlc_res {void* payload; struct vlc_res* prev; int /*<<< orphan*/  (* release ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_res*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 struct vlc_res** vlc_obj_res (int /*<<< orphan*/ *) ; 

void vlc_objres_remove(vlc_object_t *obj, void *data,
                       bool (*match)(void *, void *))
{
    struct vlc_res **restrict pp = vlc_obj_res(obj);

    /* With a doubly-linked list, this function could have constant complexity.
     * But that would require one more pointer per resource.
     *
     * Any given list should contain a fairly small number of resources,
     * and in most cases, the resources are destroyed implicitly by
     * vlc_objres_clear().
     */
    for (;;)
    {
        struct vlc_res *res = *pp;

        assert(res != NULL); /* invalid free? */

        if (match(res->payload, data))
        {
            *pp = res->prev;
            res->release(res->payload);
            free(res);
            return;
        }

        pp = &res->prev;
    }
}