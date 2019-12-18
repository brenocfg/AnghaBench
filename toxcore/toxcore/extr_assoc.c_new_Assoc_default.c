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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Assoc ;

/* Variables and functions */
 int /*<<< orphan*/ * new_Assoc (int,int,int /*<<< orphan*/  const*) ; 

Assoc *new_Assoc_default(const uint8_t *public_id)
{
    /* original 8, 251 averages to ~32k entries... probably the whole DHT :D
     * 320 entries is fine, hopefully */
    return new_Assoc(6, 15, public_id);
}