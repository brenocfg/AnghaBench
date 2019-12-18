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
 int /*<<< orphan*/  fuzz_client (int /*<<< orphan*/  const*,size_t,int) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        if (size > 65536)
                return 0;

        /* This triggers client_receive_advertise */
        fuzz_client(data, size, false);

        /* This triggers client_receive_reply */
        fuzz_client(data, size, true);

        return 0;
}