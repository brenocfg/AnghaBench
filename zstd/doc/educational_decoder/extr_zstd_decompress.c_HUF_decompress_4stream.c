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
typedef  int /*<<< orphan*/  ostream_t ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  int /*<<< orphan*/  HUF_dtable ;

/* Variables and functions */
 scalar_t__ HUF_decompress_1stream (int /*<<< orphan*/  const* const,int /*<<< orphan*/ * const,int /*<<< orphan*/ *) ; 
 size_t const IO_istream_len (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  IO_make_sub_istream (int /*<<< orphan*/ * const,size_t const) ; 
 size_t IO_read_bits (int /*<<< orphan*/ * const,int) ; 

__attribute__((used)) static size_t HUF_decompress_4stream(const HUF_dtable *const dtable,
                                     ostream_t *const out, istream_t *const in) {
    // "Compressed size is provided explicitly : in the 4-streams variant,
    // bitstreams are preceded by 3 unsigned little-endian 16-bits values. Each
    // value represents the compressed size of one stream, in order. The last
    // stream size is deducted from total compressed size and from previously
    // decoded stream sizes"
    const size_t csize1 = IO_read_bits(in, 16);
    const size_t csize2 = IO_read_bits(in, 16);
    const size_t csize3 = IO_read_bits(in, 16);

    istream_t in1 = IO_make_sub_istream(in, csize1);
    istream_t in2 = IO_make_sub_istream(in, csize2);
    istream_t in3 = IO_make_sub_istream(in, csize3);
    istream_t in4 = IO_make_sub_istream(in, IO_istream_len(in));

    size_t total_output = 0;
    // Decode each stream independently for simplicity
    // If we wanted to we could decode all 4 at the same time for speed,
    // utilizing more execution units
    total_output += HUF_decompress_1stream(dtable, out, &in1);
    total_output += HUF_decompress_1stream(dtable, out, &in2);
    total_output += HUF_decompress_1stream(dtable, out, &in3);
    total_output += HUF_decompress_1stream(dtable, out, &in4);

    return total_output;
}