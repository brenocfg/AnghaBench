#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_version; int /*<<< orphan*/  uniqueextdesc; scalar_t__ es; scalar_t__ i_es; } ;
typedef  TYPE_1__ ps_psm_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ps_psm_init( ps_psm_t *p_psm )
{
    p_psm->i_version = 0xFF;
    p_psm->i_es = 0;
    p_psm->es = 0;
    memset( &p_psm->uniqueextdesc, 0, 3 );
}