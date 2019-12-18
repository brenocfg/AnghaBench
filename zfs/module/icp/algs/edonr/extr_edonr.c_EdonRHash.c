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
typedef  int /*<<< orphan*/  EdonRState ;

/* Variables and functions */
 int /*<<< orphan*/  EdonRFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EdonRInit (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EdonRUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

void
EdonRHash(size_t hashbitlen, const uint8_t *data, size_t databitlen,
    uint8_t *hashval)
{
	EdonRState state;

	EdonRInit(&state, hashbitlen);
	EdonRUpdate(&state, data, databitlen);
	EdonRFinal(&state, hashval);
}