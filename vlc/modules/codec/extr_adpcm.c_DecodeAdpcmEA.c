#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int_fast8_t ;
typedef  int int_fast32_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_6__ {unsigned int i_channels; } ;
struct TYPE_7__ {TYPE_1__ audio; } ;
struct TYPE_8__ {TYPE_2__ fmt_out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_9__ {size_t i_block; int* prev; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMP (int,int,int) ; 
 int MAX_CHAN ; 

__attribute__((used)) static void DecodeAdpcmEA( decoder_t *p_dec, int16_t *p_sample,
                           uint8_t *p_buffer )
{
    static const int16_t EATable[]=
    {
        0x0000, 0x00F0, 0x01CC, 0x0188, 0x0000, 0x0000, 0xFF30, 0xFF24,
        0x0000, 0x0001, 0x0003, 0x0004, 0x0007, 0x0008, 0x000A, 0x000B,
        0x0000, 0xFFFF, 0xFFFD, 0xFFFC,
    };
    decoder_sys_t *p_sys  = p_dec->p_sys;
    int_fast32_t c1[MAX_CHAN], c2[MAX_CHAN];
    int_fast8_t d[MAX_CHAN];

    unsigned chans = p_dec->fmt_out.audio.i_channels;
    const uint8_t *p_end = &p_buffer[p_sys->i_block];
    int16_t *prev = p_sys->prev;
    int16_t *cur = prev + chans;

    for (unsigned c = 0; c < chans; c++)
    {
        uint8_t input = p_buffer[c];

        c1[c] = EATable[input >> 4];
        c2[c] = EATable[(input >> 4) + 4];
        d[c] = (input & 0xf) + 8;
    }

    for (p_buffer += chans; p_buffer < p_end; p_buffer += chans)
    {
        union { uint32_t u; int32_t i; } spl;

        for (unsigned c = 0; c < chans; c++)
        {
            spl.u = (p_buffer[c] & 0xf0u) << 24u;
            spl.i >>= d[c];
            spl.i = (spl.i + cur[c] * c1[c] + prev[c] * c2[c] + 0x80) >> 8;
            CLAMP(spl.i, -32768, 32767);
            prev[c] = cur[c];
            cur[c] = spl.i;

            *(p_sample++) = spl.i;
        }

        for (unsigned c = 0; c < chans; c++)
        {
            spl.u = (p_buffer[c] & 0x0fu) << 28u;
            spl.i >>= d[c];
            spl.i = (spl.i + cur[c] * c1[c] + prev[c] * c2[c] + 0x80) >> 8;
            CLAMP(spl.i, -32768, 32767);
            prev[c] = cur[c];
            cur[c] = spl.i;

            *(p_sample++) = spl.i;
        }
    }
}