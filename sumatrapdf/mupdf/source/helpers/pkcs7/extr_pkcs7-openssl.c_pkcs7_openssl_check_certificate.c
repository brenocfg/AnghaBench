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
typedef  enum pdf_signature_error { ____Placeholder_pdf_signature_error } pdf_signature_error ;

/* Variables and functions */
 int PDF_SIGNATURE_ERROR_UNKNOWN ; 

enum pdf_signature_error
pkcs7_openssl_check_certificate(char *sig, int sig_len)
{
	return PDF_SIGNATURE_ERROR_UNKNOWN;
}