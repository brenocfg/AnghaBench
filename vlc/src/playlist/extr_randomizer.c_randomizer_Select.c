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
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct randomizer {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int randomizer_IndexOf (struct randomizer*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  randomizer_SelectIndex (struct randomizer*,size_t) ; 

void
randomizer_Select(struct randomizer *r, const vlc_playlist_item_t *item)
{
    ssize_t index = randomizer_IndexOf(r, item);
    assert(index != -1); /* item must exist */
    randomizer_SelectIndex(r, (size_t) index);
}