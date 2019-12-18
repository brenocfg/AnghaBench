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
struct TYPE_4__ {int method; } ;
struct TYPE_5__ {TYPE_1__ strf; } ;
typedef  TYPE_2__ pdf_crypt ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
#define  PDF_CRYPT_AESV2 132 
#define  PDF_CRYPT_AESV3 131 
#define  PDF_CRYPT_NONE 130 
#define  PDF_CRYPT_RC4 129 
#define  PDF_CRYPT_UNKNOWN 128 

char *
pdf_crypt_method(fz_context *ctx, pdf_crypt *crypt)
{
	if (crypt)
	{
		switch (crypt->strf.method)
		{
		case PDF_CRYPT_NONE: return "None";
		case PDF_CRYPT_RC4: return "RC4";
		case PDF_CRYPT_AESV2: return "AES";
		case PDF_CRYPT_AESV3: return "AES";
		case PDF_CRYPT_UNKNOWN: return "Unknown";
		}
	}
	return "None";
}