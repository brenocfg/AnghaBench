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
typedef  int /*<<< orphan*/  vlc_sem_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  enum input_item_preparse_status { ____Placeholder_input_item_preparse_status } input_item_preparse_status ;

/* Variables and functions */
 int ITEM_PREPARSE_TIMEOUT ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void input_item_preparse_timeout( input_item_t *item,
                                         enum input_item_preparse_status status,
                                         void *user_data )
{
    VLC_UNUSED(item);
    vlc_sem_t *p_sem = user_data;

    assert( status == ITEM_PREPARSE_TIMEOUT );
    vlc_sem_post(p_sem);
}