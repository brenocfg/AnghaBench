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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_1__ aout_stream_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  Play (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 

__attribute__((used)) static HRESULT StreamPlay( aout_stream_t *s, block_t *block, vlc_tick_t date )
{
    (void) date;
    return Play( VLC_OBJECT(s), s->sys, block );
}