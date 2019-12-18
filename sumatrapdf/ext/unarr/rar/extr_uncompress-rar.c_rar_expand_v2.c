#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
struct ar_archive_rar_uncomp_v2 {size_t channel; size_t numchannels; int lastoffset; int lastlength; int* oldoffset; int oldoffsetindex; int /*<<< orphan*/  offsetcode; int /*<<< orphan*/  lengthcode; int /*<<< orphan*/  maincode; int /*<<< orphan*/  channeldelta; int /*<<< orphan*/ * audiostate; int /*<<< orphan*/ * audiocode; scalar_t__ audioblock; } ;
typedef  int /*<<< orphan*/  offsetbits ;
typedef  int /*<<< orphan*/  offsetbases ;
typedef  int /*<<< orphan*/  lengthbits ;
typedef  int /*<<< orphan*/  lengthbases ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
struct TYPE_10__ {struct ar_archive_rar_uncomp_v2 v2; } ;
struct TYPE_13__ {int start_new_table; int /*<<< orphan*/  lzss; TYPE_1__ state; } ;
struct TYPE_12__ {scalar_t__ size_total; } ;
struct TYPE_11__ {scalar_t__ entry_size_uncompressed; } ;
struct TYPE_14__ {TYPE_4__ uncomp; TYPE_3__ solid; TYPE_2__ super; } ;
typedef  TYPE_5__ ar_archive_rar ;
typedef  int /*<<< orphan*/  LZSS ;

/* Variables and functions */
 scalar_t__ br_bits (TYPE_5__*,int const) ; 
 int /*<<< orphan*/  br_check (TYPE_5__*,int const) ; 
 int /*<<< orphan*/  lzss_emit_literal (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lzss_emit_match (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ lzss_position (int /*<<< orphan*/ *) ; 
 int rar_decode_audio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rar_read_next_symbol (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

int64_t rar_expand_v2(ar_archive_rar *rar, int64_t end)
{
    static const uint8_t lengthbases[] =
        {   0,   1,   2,   3,   4,   5,   6,
            7,   8,  10,  12,  14,  16,  20,
           24,  28,  32,  40,  48,  56,  64,
           80,  96, 112, 128, 160, 192, 224 };
    static const uint8_t lengthbits[] =
        { 0, 0, 0, 0, 0, 0, 0,
          0, 1, 1, 1, 1, 2, 2,
          2, 2, 3, 3, 3, 3, 4,
          4, 4, 4, 5, 5, 5, 5 };
    static const int32_t offsetbases[] =
        {       0,       1,       2,       3,       4,       6,
                8,      12,      16,      24,      32,      48,
               64,      96,     128,     192,     256,     384,
              512,     768,    1024,    1536,    2048,    3072,
             4096,    6144,    8192,   12288,   16384,   24576,
            32768,   49152,   65536,   98304,  131072,  196608,
           262144,  327680,  393216,  458752,  524288,  589824,
           655360,  720896,  786432,  851968,  917504,  983040 };
    static const uint8_t offsetbits[] =
        {  0,  0,  0,  0,  1,  1,  2,  2,  3,  3,  4,  4,
           5,  5,  6,  6,  7,  7,  8,  8,  9,  9, 10, 10,
          11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16,
          16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 };
    static const uint8_t shortbases[] =
        { 0, 4, 8, 16, 32, 64, 128, 192 };
    static const uint8_t shortbits[] =
        { 2, 2, 3, 4, 5, 6, 6, 6 };

    struct ar_archive_rar_uncomp_v2 *uncomp_v2 = &rar->uncomp.state.v2;
    LZSS *lzss = &rar->uncomp.lzss;
    int symbol, offs, len;

    if ((uint64_t)end > rar->super.entry_size_uncompressed + rar->solid.size_total)
        end = rar->super.entry_size_uncompressed + rar->solid.size_total;

    for (;;) {
        if (lzss_position(lzss) >= end)
            return end;

        if (uncomp_v2->audioblock) {
            uint8_t byte;
            symbol = rar_read_next_symbol(rar, &uncomp_v2->audiocode[uncomp_v2->channel]);
            if (symbol < 0)
                return -1;
            if (symbol == 256) {
                rar->uncomp.start_new_table = true;
                return lzss_position(lzss);
            }
            byte = rar_decode_audio(&uncomp_v2->audiostate[uncomp_v2->channel], &uncomp_v2->channeldelta, (int8_t)(uint8_t)symbol);
            uncomp_v2->channel++;
            if (uncomp_v2->channel == uncomp_v2->numchannels)
                uncomp_v2->channel = 0;
            lzss_emit_literal(lzss, byte);
            continue;
        }

        symbol = rar_read_next_symbol(rar, &uncomp_v2->maincode);
        if (symbol < 0)
            return -1;
        if (symbol < 256) {
            lzss_emit_literal(lzss, (uint8_t)symbol);
            continue;
        }
        if (symbol == 256) {
            offs = uncomp_v2->lastoffset;
            len = uncomp_v2->lastlength;
        }
        else if (symbol <= 260) {
            int idx = symbol - 256;
            int lensymbol = rar_read_next_symbol(rar, &uncomp_v2->lengthcode);
            offs = uncomp_v2->oldoffset[(uncomp_v2->oldoffsetindex - idx) & 0x03];
            if (lensymbol < 0 || lensymbol > (int)(sizeof(lengthbases) / sizeof(lengthbases[0])) || lensymbol > (int)(sizeof(lengthbits) / sizeof(lengthbits[0]))) {
                warn("Invalid data in bitstream");
                return -1;
            }
            len = lengthbases[lensymbol] + 2;
            if (lengthbits[lensymbol] > 0) {
                if (!br_check(rar, lengthbits[lensymbol]))
                    return -1;
                len += (uint8_t)br_bits(rar, lengthbits[lensymbol]);
            }
            if (offs >= 0x40000)
                len++;
            if (offs >= 0x2000)
                len++;
            if (offs >= 0x101)
                len++;
        }
        else if (symbol <= 268) {
            int idx = symbol - 261;
            offs = shortbases[idx] + 1;
            if (shortbits[idx] > 0) {
                if (!br_check(rar, shortbits[idx]))
                    return -1;
                offs += (uint8_t)br_bits(rar, shortbits[idx]);
            }
            len = 2;
        }
        else if (symbol == 269) {
            rar->uncomp.start_new_table = true;
            return lzss_position(lzss);
        }
        else {
            int idx = symbol - 270;
            int offssymbol;
            if (idx > (int)(sizeof(lengthbases) / sizeof(lengthbases[0])) || idx > (int)(sizeof(lengthbits) / sizeof(lengthbits[0]))) {
                warn("Invalid data in bitstream");
                return -1;
            }
            len = lengthbases[idx] + 3;
            if (lengthbits[idx] > 0) {
                if (!br_check(rar, lengthbits[idx]))
                    return -1;
                len += (uint8_t)br_bits(rar, lengthbits[idx]);
            }
            offssymbol = rar_read_next_symbol(rar, &uncomp_v2->offsetcode);
            if (offssymbol < 0 || offssymbol > (int)(sizeof(offsetbases) / sizeof(offsetbases[0])) || offssymbol > (int)(sizeof(offsetbits) / sizeof(offsetbits[0]))) {
                warn("Invalid data in bitstream");
                return -1;
            }
            offs = offsetbases[offssymbol] + 1;
            if (offsetbits[offssymbol] > 0) {
                if (!br_check(rar, offsetbits[offssymbol]))
                    return -1;
                offs += (int)br_bits(rar, offsetbits[offssymbol]);
            }
            if (offs >= 0x40000)
                len++;
            if (offs >= 0x2000)
                len++;
        }

        uncomp_v2->lastoffset = uncomp_v2->oldoffset[uncomp_v2->oldoffsetindex++ & 0x03] = offs;
        uncomp_v2->lastlength = len;

        lzss_emit_match(lzss, offs, len);
    }
}