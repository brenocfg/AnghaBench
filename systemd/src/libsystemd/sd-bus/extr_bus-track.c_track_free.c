#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  userdata; int /*<<< orphan*/  (* destroy_callback ) (int /*<<< orphan*/ ) ;TYPE_4__* bus; int /*<<< orphan*/  names; scalar_t__ in_list; } ;
typedef  TYPE_1__ sd_bus_track ;
struct TYPE_12__ {int /*<<< orphan*/  tracks; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_track_remove_from_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 TYPE_4__* sd_bus_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracks ; 

__attribute__((used)) static sd_bus_track *track_free(sd_bus_track *track) {
        assert(track);

        if (track->in_list)
                LIST_REMOVE(tracks, track->bus->tracks, track);

        bus_track_remove_from_queue(track);
        track->names = hashmap_free(track->names);
        track->bus = sd_bus_unref(track->bus);

        if (track->destroy_callback)
                track->destroy_callback(track->userdata);

        return mfree(track);
}