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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ts_header ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void writeTsPacketWDiscontinuity( uint8_t *p_buf, uint16_t i_pid,
                                         const uint8_t *p_payload, uint8_t i_payload )
{
    uint8_t ts_header[] = {
        0x00, 0x00, 0x00, 0x00,                /* TP extra header (ATC) */
        0x47,
        0x40 | ((i_pid & 0x1f00) >> 8), i_pid & 0xFF, /* PUSI + PID */
        i_payload ? 0x30 : 0x20,               /* adaptation field, payload / no payload */
        192 - (4 + 5) - i_payload,             /* adaptation field length */
        0x82,                                  /* af: discontinuity indicator + priv data */
        0x0E,                                  /* priv data size */
         'V',  'L',  'C',  '_',
         'D',  'I',  'S',  'C',  'O',  'N',  'T',  'I',  'N',  'U',
    };

    memcpy( p_buf, ts_header, sizeof(ts_header) );
    memset( &p_buf[sizeof(ts_header)], 0xFF, 192 - sizeof(ts_header) - i_payload );
    if( i_payload )
        memcpy( &p_buf[192 - i_payload], p_payload, i_payload );
}