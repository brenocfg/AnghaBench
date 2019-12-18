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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ fz_bidi_chartype ;

/* Variables and functions */
 scalar_t__ BDI_N ; 
 scalar_t__ BDI_S ; 
 scalar_t__ BDI_WS ; 
 scalar_t__ class_from_ch_ws (int /*<<< orphan*/ ) ; 

__attribute__((used)) static fz_bidi_chartype class_from_ch_n(uint32_t ch)
{
	fz_bidi_chartype from_ch_ws = class_from_ch_ws(ch);
	if (from_ch_ws == BDI_S || from_ch_ws == BDI_WS)
		return BDI_N;
	return from_ch_ws;
}