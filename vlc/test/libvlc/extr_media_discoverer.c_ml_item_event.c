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
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  item; } ;
struct TYPE_4__ {TYPE_1__ media_list_item_added; } ;
struct libvlc_event_t {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* libvlc_media_get_mrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_log (char*,char const*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ml_item_event(const struct libvlc_event_t *p_ev, const char *psz_event)
{
    char *psz_mrl = libvlc_media_get_mrl(p_ev->u.media_list_item_added.item);
    assert(psz_mrl);

    test_log("item %s(%d): '%s'\n", psz_event,
             p_ev->u.media_list_item_added.index, psz_mrl);
    free(psz_mrl);
}