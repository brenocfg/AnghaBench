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
struct tiff {unsigned int ep; unsigned int bp; unsigned int rp; } ;

/* Variables and functions */
 int /*<<< orphan*/  tiff_readbyte (struct tiff*) ; 

__attribute__((used)) static void
tiff_read_bytes(unsigned char *p, struct tiff *tiff, unsigned ofs, unsigned n)
{
	if (ofs > (unsigned)(tiff->ep - tiff->bp))
		ofs = (unsigned)(tiff->ep - tiff->bp);
	tiff->rp = tiff->bp + ofs;

	while (n--)
		*p++ = tiff_readbyte(tiff);
}