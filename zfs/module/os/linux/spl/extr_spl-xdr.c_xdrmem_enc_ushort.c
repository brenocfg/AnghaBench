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
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  xdrmem_enc_uint32 (int /*<<< orphan*/ *,unsigned short) ; 

__attribute__((used)) static bool_t
xdrmem_enc_ushort(XDR *xdrs, unsigned short *usp)
{
	BUILD_BUG_ON(sizeof (unsigned short) != 2);

	return (xdrmem_enc_uint32(xdrs, *usp));
}