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
typedef  scalar_t__ uint_fast8_t ;
typedef  scalar_t__ uint8_t ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ WINDOW_UPDATE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  external_tls ; 
 int vlc_tls_Read (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void conn_expect(uint_fast8_t wanted)
{
    size_t len;
    ssize_t val;
    uint8_t hdr[9];
    uint8_t got;

    do {
        val = vlc_tls_Read(external_tls, hdr, 9, true);
        assert(val == 9);
        assert(hdr[0] == 0);

        /* Check type. We do not currently validate WINDOW_UPDATE. */
        got = hdr[3];
        assert(wanted == got || WINDOW_UPDATE == got);

        len = (hdr[1] << 8) | hdr[2];
        if (len > 0)
        {
            char buf[len];

            val = vlc_tls_Read(external_tls, buf, len, true);
            assert(val == (ssize_t)len);
        }
    }
    while (got != wanted);
}