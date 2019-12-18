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
typedef  int uint8_t ;
struct hpack_decoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int hpack_decode_hdr_index (struct hpack_decoder*,int const**,size_t*,char**,char**) ; 
 int hpack_decode_hdr_indexed (struct hpack_decoder*,int const**,size_t*,char**,char**) ; 
 int hpack_decode_hdr_noindex (struct hpack_decoder*,int const**,size_t*,char**,char**) ; 
 int hpack_decode_tbl_update (struct hpack_decoder*,int const**,size_t*,char**,char**) ; 

__attribute__((used)) static int hpack_decode_hdr(struct hpack_decoder *dec,
                            const uint8_t **restrict datap,
                            size_t *restrict lengthp,
                            char **restrict namep,
                            char **restrict valuep)
{
    int (*cb)(struct hpack_decoder *, const uint8_t **, size_t *,
              char **, char **);

    assert(*lengthp >= 1);

    uint8_t b = **datap;

    if (b & 0x80)
        cb = hpack_decode_hdr_indexed;
    else if (b & 0x40)
        cb = hpack_decode_hdr_index;
    else if (b & 0x20)
        cb = hpack_decode_tbl_update;
    else
    /* NOTE: never indexed and not indexed are treated identically */
        cb = hpack_decode_hdr_noindex;

    return cb(dec, datap, lengthp, namep, valuep);
}