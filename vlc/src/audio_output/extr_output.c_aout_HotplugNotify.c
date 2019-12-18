#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; TYPE_3__* list; } ;
struct TYPE_9__ {TYPE_1__ dev; } ;
typedef  TYPE_2__ aout_owner_t ;
struct TYPE_10__ {struct TYPE_10__* name; struct TYPE_10__* next; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ aout_dev_t ;

/* Variables and functions */
 TYPE_2__* aout_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* strdup (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aout_HotplugNotify (audio_output_t *aout,
                                const char *id, const char *name)
{
    aout_owner_t *owner = aout_owner (aout);
    aout_dev_t *dev, **pp = &owner->dev.list;

    vlc_mutex_lock (&owner->dev.lock);
    while ((dev = *pp) != NULL)
    {
        if (!strcmp (id, dev->id))
            break;
        pp = &dev->next;
    }

    if (name != NULL)
    {
        if (dev == NULL) /* Added device */
        {
            dev = malloc (sizeof (*dev) + strlen (id));
            if (unlikely(dev == NULL))
                goto out;
            dev->next = NULL;
            strcpy (dev->id, id);
            *pp = dev;
            owner->dev.count++;
        }
        else /* Modified device */
            free (dev->name);
        dev->name = strdup (name);
    }
    else
    {
        if (dev != NULL) /* Removed device */
        {
            owner->dev.count--;
            *pp = dev->next;
            free (dev->name);
            free (dev);
        }
    }
out:
    vlc_mutex_unlock (&owner->dev.lock);
}