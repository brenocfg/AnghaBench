#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ method; } ;
struct TYPE_5__ {TYPE_1__ strf; } ;
typedef  TYPE_2__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ PDF_CRYPT_AESV2 ; 
 scalar_t__ PDF_CRYPT_AESV3 ; 

int pdf_encrypted_len(fz_context *ctx, pdf_crypt *crypt, int num, int gen, int len)
{
	if (crypt == NULL)
		return len;

	if (crypt->strf.method == PDF_CRYPT_AESV2 || crypt->strf.method == PDF_CRYPT_AESV3)
	{
		len += 16; /* 16 for IV */
		if ((len & 15) == 0)
			len += 16; /* Another 16 if our last block is full anyway */
		len = (len + 15) & ~15; /* And pad to the block */
	}

	return len;
}