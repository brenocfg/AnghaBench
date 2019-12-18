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
struct tiff {scalar_t__ order; } ;

/* Variables and functions */
 scalar_t__ TII ; 
 unsigned int tiff_readbyte (struct tiff*) ; 

__attribute__((used)) static inline unsigned readshort(struct tiff *tiff)
{
	unsigned a = tiff_readbyte(tiff);
	unsigned b = tiff_readbyte(tiff);
	if (tiff->order == TII)
		return (b << 8) | a;
	return (a << 8) | b;
}