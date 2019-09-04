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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  data32 ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 scalar_t__ MESSENGER_STATE_COOKIE_GLOBAL ; 
 int /*<<< orphan*/  MESSENGER_STATE_COOKIE_TYPE ; 
 int /*<<< orphan*/  lendian_to_host32 (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int load_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  messenger_load_state_callback ; 

int messenger_load(Messenger *m, const uint8_t *data, uint32_t length)
{
    uint32_t data32[2];
    uint32_t cookie_len = sizeof(data32);

    if (length < cookie_len)
        return -1;

    memcpy(data32, data, sizeof(uint32_t));
    lendian_to_host32(data32 + 1, data + sizeof(uint32_t));

    if (!data32[0] && (data32[1] == MESSENGER_STATE_COOKIE_GLOBAL))
        return load_state(messenger_load_state_callback, m, data + cookie_len,
                          length - cookie_len, MESSENGER_STATE_COOKIE_TYPE);
    else
        return -1;
}