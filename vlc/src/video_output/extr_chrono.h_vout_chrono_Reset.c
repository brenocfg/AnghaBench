#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  avg_initial; int /*<<< orphan*/  shift; } ;
typedef  TYPE_1__ vout_chrono_t ;

/* Variables and functions */
 int /*<<< orphan*/  vout_chrono_Clean (TYPE_1__*) ; 
 int /*<<< orphan*/  vout_chrono_Init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vout_chrono_Reset(vout_chrono_t *chrono)
{
    vout_chrono_t ch = *chrono;
    vout_chrono_Clean(chrono);
    vout_chrono_Init(chrono, ch.shift, ch.avg_initial);
}