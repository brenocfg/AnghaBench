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
typedef  int /*<<< orphan*/  weights ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  ostream_t ;
typedef  int /*<<< orphan*/  istream_t ;
typedef  int /*<<< orphan*/  HUF_dtable ;

/* Variables and functions */
 int HUF_MAX_SYMBS ; 
 int /*<<< orphan*/  HUF_init_dtable_usingweights (int /*<<< orphan*/ * const,int*,int) ; 
 int* IO_get_read_ptr (int /*<<< orphan*/ * const,size_t const) ; 
 int /*<<< orphan*/  IO_make_ostream (int*,int) ; 
 int /*<<< orphan*/  IO_make_sub_istream (int /*<<< orphan*/ * const,int const) ; 
 int IO_read_bits (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  fse_decode_hufweights (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void decode_huf_table(HUF_dtable *const dtable, istream_t *const in) {
    // "All literal values from zero (included) to last present one (excluded)
    // are represented by Weight with values from 0 to Max_Number_of_Bits."

    // "This is a single byte value (0-255), which describes how to decode the list of weights."
    const u8 header = IO_read_bits(in, 8);

    u8 weights[HUF_MAX_SYMBS];
    memset(weights, 0, sizeof(weights));

    int num_symbs;

    if (header >= 128) {
        // "This is a direct representation, where each Weight is written
        // directly as a 4 bits field (0-15). The full representation occupies
        // ((Number_of_Symbols+1)/2) bytes, meaning it uses a last full byte
        // even if Number_of_Symbols is odd. Number_of_Symbols = headerByte -
        // 127"
        num_symbs = header - 127;
        const size_t bytes = (num_symbs + 1) / 2;

        const u8 *const weight_src = IO_get_read_ptr(in, bytes);

        for (int i = 0; i < num_symbs; i++) {
            // "They are encoded forward, 2
            // weights to a byte with the first weight taking the top four bits
            // and the second taking the bottom four (e.g. the following
            // operations could be used to read the weights: Weight[0] =
            // (Byte[0] >> 4), Weight[1] = (Byte[0] & 0xf), etc.)."
            if (i % 2 == 0) {
                weights[i] = weight_src[i / 2] >> 4;
            } else {
                weights[i] = weight_src[i / 2] & 0xf;
            }
        }
    } else {
        // The weights are FSE encoded, decode them before we can construct the
        // table
        istream_t fse_stream = IO_make_sub_istream(in, header);
        ostream_t weight_stream = IO_make_ostream(weights, HUF_MAX_SYMBS);
        fse_decode_hufweights(&weight_stream, &fse_stream, &num_symbs);
    }

    // Construct the table using the decoded weights
    HUF_init_dtable_usingweights(dtable, weights, num_symbs);
}