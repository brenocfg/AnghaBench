#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_7__ {int next_word; int next_word_bytes; int offset; int C; int CT; TYPE_1__* ws; } ;
struct TYPE_6__ {int (* get_next_word ) (TYPE_1__*,int,int*) ;} ;
typedef  TYPE_1__ Jbig2WordStream ;
typedef  TYPE_2__ Jbig2ArithState ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (TYPE_1__*,int,int*) ; 
 int stub2 (TYPE_1__*,int,int*) ; 

__attribute__((used)) static void
jbig2_arith_bytein(Jbig2ArithState *as)
{
    int new_bytes;
    byte B;

    /* invariant: as->next_word_bytes > 0 */

    /* Figure G.3 */
    B = (byte)((as->next_word >> 24) & 0xFF);
    if (B == 0xFF) {
        byte B1;

        if (as->next_word_bytes == 1) {
            Jbig2WordStream *ws = as->ws;

            new_bytes = ws->get_next_word(ws, as->offset, &as->next_word);
            as->next_word_bytes = new_bytes;
            as->offset += new_bytes;

            B1 = (byte)((as->next_word >> 24) & 0xFF);
            if (B1 > 0x8F) {
#ifdef JBIG2_DEBUG_ARITH
                fprintf(stderr, "read %02x (aa)\n", B);
#endif
#ifndef SOFTWARE_CONVENTION
                as->C += 0xFF00;
#endif
                as->CT = 8;
                as->next_word = 0xFF000000 | (as->next_word >> 8);
                as->next_word_bytes = 4;
                as->offset--;
            } else {
#ifdef JBIG2_DEBUG_ARITH
                fprintf(stderr, "read %02x (a)\n", B);
#endif
#ifdef SOFTWARE_CONVENTION
                as->C += 0xFE00 - (B1 << 9);
#else
                as->C += B1 << 9;
#endif
                as->CT = 7;
            }
        } else {
            B1 = (byte)((as->next_word >> 16) & 0xFF);
            if (B1 > 0x8F) {
#ifdef JBIG2_DEBUG_ARITH
                fprintf(stderr, "read %02x (ba)\n", B);
#endif
#ifndef SOFTWARE_CONVENTION
                as->C += 0xFF00;
#endif
                as->CT = 8;
            } else {
                as->next_word_bytes--;
                as->next_word <<= 8;
#ifdef JBIG2_DEBUG_ARITH
                fprintf(stderr, "read %02x (b)\n", B);
#endif

#ifdef SOFTWARE_CONVENTION
                as->C += 0xFE00 - (B1 << 9);
#else
                as->C += (B1 << 9);
#endif
                as->CT = 7;
            }
        }
    } else {
#ifdef JBIG2_DEBUG_ARITH
        fprintf(stderr, "read %02x\n", B);
#endif
        as->CT = 8;
        as->next_word <<= 8;
        as->next_word_bytes--;
        if (as->next_word_bytes == 0) {
            Jbig2WordStream *ws = as->ws;

            new_bytes = ws->get_next_word(ws, as->offset, &as->next_word);
            as->offset += new_bytes;
            as->next_word_bytes = new_bytes;
        }
        B = (byte)((as->next_word >> 24) & 0xFF);
#ifdef SOFTWARE_CONVENTION
        as->C += 0xFF00 - (B << 8);
#else
        as->C += (B << 8);
#endif
    }
}