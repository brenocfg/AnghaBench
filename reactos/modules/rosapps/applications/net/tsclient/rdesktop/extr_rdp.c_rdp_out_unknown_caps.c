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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static void
rdp_out_unknown_caps(STREAM s, uint16 id, uint16 length, const uint8 * caps)
{
	out_uint16_le(s, id);
	out_uint16_le(s, length);

	out_uint8p(s, caps, length - 4);
}