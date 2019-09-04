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

/* Variables and functions */
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  response_callback_connection_id ; 
 int /*<<< orphan*/  response_callback_good ; 
 int /*<<< orphan*/  response_callback_public_key ; 
 scalar_t__ set_tcp_connection_number (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int response_callback(void *object, uint8_t connection_id, const uint8_t *public_key)
{
    if (set_tcp_connection_number(object - 2, connection_id, 7) != 0)
        return 1;

    response_callback_connection_id = connection_id;
    memcpy(response_callback_public_key, public_key, crypto_box_PUBLICKEYBYTES);
    response_callback_good++;
    return 0;
}