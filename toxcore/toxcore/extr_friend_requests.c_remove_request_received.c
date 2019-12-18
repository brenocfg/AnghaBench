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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * received_requests; } ;
typedef  TYPE_1__ Friend_Requests ;

/* Variables and functions */
 size_t MAX_RECEIVED_STORED ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ id_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int remove_request_received(Friend_Requests *fr, const uint8_t *real_pk)
{
    uint32_t i;

    for (i = 0; i < MAX_RECEIVED_STORED; ++i) {
        if (id_equal(fr->received_requests[i], real_pk)) {
            sodium_memzero(fr->received_requests[i], crypto_box_PUBLICKEYBYTES);
            return 0;
        }
    }

    return -1;
}