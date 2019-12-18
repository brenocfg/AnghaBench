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
struct decoder_owner {int /*<<< orphan*/  reload; } ;

/* Variables and functions */
 int /*<<< orphan*/  RELOAD_DECODER ; 
 int RELOAD_NO_REQUEST ; 
 int /*<<< orphan*/  atomic_compare_exchange_strong (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void RequestReload( struct decoder_owner *p_owner )
{
    /* Don't override reload if it's RELOAD_DECODER_AOUT */
    int expected = RELOAD_NO_REQUEST;
    atomic_compare_exchange_strong( &p_owner->reload, &expected, RELOAD_DECODER );
}