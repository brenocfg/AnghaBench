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

/* Variables and functions */
 size_t CE_NAMEMASK ; 
 unsigned int CE_STAGESHIFT ; 

__attribute__((used)) static inline unsigned create_ce_flags(size_t len, unsigned stage)
{
    if (len >= CE_NAMEMASK)
        len = CE_NAMEMASK;
    return (len | (stage << CE_STAGESHIFT));
}