#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; TYPE_1__* data; } ;
struct spu_channel {TYPE_2__ entries; } ;
struct TYPE_3__ {int subpic; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  subpicture_Delete (int) ; 
 int /*<<< orphan*/  vlc_vector_remove (TYPE_2__*,size_t) ; 

__attribute__((used)) static void spu_channel_DeleteAt(struct spu_channel *channel, size_t index)
{
    assert(index < channel->entries.size);
    assert(channel->entries.data[index].subpic);

    subpicture_Delete(channel->entries.data[index].subpic);
    vlc_vector_remove(&channel->entries, index);
}