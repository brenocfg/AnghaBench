#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ auto_preparse; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_IsPreparsed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Preparse (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
vlc_playlist_AutoPreparse(vlc_playlist_t *playlist, input_item_t *input)
{
    if (playlist->auto_preparse && !input_item_IsPreparsed(input))
        vlc_playlist_Preparse(playlist, input);
}