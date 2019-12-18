#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_5__ {int esc_len; int /*<<< orphan*/  esc; } ;
typedef  TYPE_1__ iso2022_esc_t ;
struct TYPE_6__ {scalar_t__ mode; } ;
typedef  TYPE_2__ csconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 size_t ISO2022JP_CS_ASCII ; 
 scalar_t__ ISO2022_MODE (size_t,scalar_t__) ; 
 size_t ISO2022_MODE_CS (scalar_t__) ; 
 scalar_t__ ISO2022_MODE_SHIFT (scalar_t__) ; 
 scalar_t__ ISO2022_SI ; 
 int /*<<< orphan*/  iso2022_SI_seq ; 
 TYPE_1__* iso2022jp_esc ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int seterror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iso2022jp_flush(csconv_t *cv, uchar *buf, int bufsize)
{
    iso2022_esc_t *iesc = iso2022jp_esc;
    int esc_len;

    if (cv->mode != ISO2022_MODE(ISO2022JP_CS_ASCII, ISO2022_SI))
    {
        esc_len = 0;
        if (ISO2022_MODE_SHIFT(cv->mode) != ISO2022_SI)
            esc_len += 1;
        if (ISO2022_MODE_CS(cv->mode) != ISO2022JP_CS_ASCII)
            esc_len += iesc[ISO2022JP_CS_ASCII].esc_len;
        if (bufsize < esc_len)
            return seterror(E2BIG);

        esc_len = 0;
        if (ISO2022_MODE_SHIFT(cv->mode) != ISO2022_SI)
        {
            memcpy(buf, iso2022_SI_seq, 1);
            esc_len += 1;
        }
        if (ISO2022_MODE_CS(cv->mode) != ISO2022JP_CS_ASCII)
        {
            memcpy(buf + esc_len, iesc[ISO2022JP_CS_ASCII].esc,
                    iesc[ISO2022JP_CS_ASCII].esc_len);
            esc_len += iesc[ISO2022JP_CS_ASCII].esc_len;
        }
        return esc_len;
    }
    return 0;
}