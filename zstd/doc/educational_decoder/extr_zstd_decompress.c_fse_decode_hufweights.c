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
typedef  int /*<<< orphan*/  FSE_dtable ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_decode_header (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int const) ; 
 int FSE_decompress_interleaved2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  FSE_free_dtable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fse_decode_hufweights(ostream_t *weights, istream_t *const in,
                                    int *const num_symbs) {
    const int MAX_ACCURACY_LOG = 7;

    FSE_dtable dtable;

    // "An FSE bitstream starts by a header, describing probabilities
    // distribution. It will create a Decoding Table. For a list of Huffman
    // weights, maximum accuracy is 7 bits."
    FSE_decode_header(&dtable, in, MAX_ACCURACY_LOG);

    // Decode the weights
    *num_symbs = FSE_decompress_interleaved2(&dtable, weights, in);

    FSE_free_dtable(&dtable);
}