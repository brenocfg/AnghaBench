#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ i_item_id; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 TYPE_1__* BOXDATA (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool MatchInfeID( const MP4_Box_t *p_infe, void *priv )
{
    return BOXDATA(p_infe)->i_item_id == *((uint32_t *) priv);
}