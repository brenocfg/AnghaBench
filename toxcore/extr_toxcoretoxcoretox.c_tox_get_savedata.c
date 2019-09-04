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
typedef  int /*<<< orphan*/  Tox ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  messenger_save (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void tox_get_savedata(const Tox *tox, uint8_t *data)
{
    if (data) {
        const Messenger *m = tox;
        messenger_save(m, data);
    }
}