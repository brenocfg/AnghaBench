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
struct TYPE_5__ {int num; int refs; int /*<<< orphan*/ * display; int /*<<< orphan*/  device; int /*<<< orphan*/  vdp; int /*<<< orphan*/ * name; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ vdp_instance_t ;
typedef  scalar_t__ VdpStatus ;

/* Variables and functions */
 scalar_t__ VDP_STATUS_ERROR ; 
 scalar_t__ VDP_STATUS_OK ; 
 scalar_t__ VDP_STATUS_RESOURCES ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int XDefaultScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (char const*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vdp_create_x11 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VdpStatus vdp_instance_create(const char *name, int num,
                                     vdp_instance_t **pp)
{
    size_t namelen = (name != NULL) ? (strlen(name) + 1) : 0;
    vdp_instance_t *vi = malloc(sizeof (*vi) + namelen);

    if (unlikely(vi == NULL))
        return VDP_STATUS_RESOURCES;

    vi->display = XOpenDisplay(name);
    if (vi->display == NULL)
    {
        free(vi);
        return VDP_STATUS_ERROR;
    }

    vi->next = NULL;
    if (name != NULL)
    {
        vi->name = (void *)(vi + 1);
        memcpy(vi->name, name, namelen);
    }
    else
        vi->name = NULL;
    if (num >= 0)
        vi->num = num;
    else
        vi->num = XDefaultScreen(vi->display);
    vi->refs = 1;

    VdpStatus err = vdp_create_x11(vi->display, vi->num,
                                   &vi->vdp, &vi->device);
    if (err != VDP_STATUS_OK)
    {
        XCloseDisplay(vi->display);
        free(vi);
        return err;
    }
    *pp = vi;
    return VDP_STATUS_OK;
}