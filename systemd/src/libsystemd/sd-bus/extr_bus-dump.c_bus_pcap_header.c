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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int magic_number; int version_major; int version_minor; int network; scalar_t__ snaplen; int /*<<< orphan*/  sigfigs; int /*<<< orphan*/  thiszone; } ;
typedef  TYPE_1__ pcap_hdr_t ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int fflush_and_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdout ; 

int bus_pcap_header(size_t snaplen, FILE *f) {

        pcap_hdr_t hdr = {
                .magic_number = 0xa1b2c3d4U,
                .version_major = 2,
                .version_minor = 4,
                .thiszone = 0, /* UTC */
                .sigfigs = 0,
                .network = 231, /* D-Bus */
        };

        if (!f)
                f = stdout;

        assert(snaplen > 0);
        assert((size_t) (uint32_t) snaplen == snaplen);

        hdr.snaplen = (uint32_t) snaplen;

        fwrite(&hdr, 1, sizeof(hdr), f);

        return fflush_and_check(f);
}