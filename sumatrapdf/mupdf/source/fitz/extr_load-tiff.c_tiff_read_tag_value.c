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
#define  TBYTE 131 
#define  TLONG 130 
#define  TRATIONAL 129 
#define  TSHORT 128 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  readshort (struct tiff*) ; 
 int /*<<< orphan*/  tiff_readbyte (struct tiff*) ; 
 void* tiff_readlong (struct tiff*) ; 

__attribute__((used)) static void
tiff_read_tag_value(unsigned *p, struct tiff *tiff, unsigned type, unsigned ofs, unsigned n)
{
	unsigned den;

	if (ofs > (unsigned)(tiff->ep - tiff->bp))
		ofs = (unsigned)(tiff->ep - tiff->bp);
	tiff->rp = tiff->bp + ofs;

	while (n--)
	{
		switch (type)
		{
		case TRATIONAL:
			*p = tiff_readlong(tiff);
			den = tiff_readlong(tiff);
			if (den)
				*p = *p / den;
			else
				*p = UINT_MAX;
			p ++;
			break;
		case TBYTE: *p++ = tiff_readbyte(tiff); break;
		case TSHORT: *p++ = readshort(tiff); break;
		case TLONG: *p++ = tiff_readlong(tiff); break;
		default: *p++ = 0; break;
		}
	}
}