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

/* Variables and functions */

__attribute__((used)) static bool IsWellKnownPayload (int type)
{
    switch (type)
    {   /* Should be in sync with modules/demux/rtp.c */
        case  0: /* PCMU/8000 */
        case  3:
        case  8: /* PCMA/8000 */
        case 10: /* L16/44100/2 */
        case 11: /* L16/44100 */
        case 12:
        case 14: /* MPA/90000 */
        case 32: /* MPV/90000 */
        case 33: /* MP2/90000 */
            return true;
   }
   return false;
}