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
#define  PDF_SIGNATURE_ERROR_DIGEST_FAILURE 135 
#define  PDF_SIGNATURE_ERROR_NOT_TRUSTED 134 
#define  PDF_SIGNATURE_ERROR_NO_CERTIFICATE 133 
#define  PDF_SIGNATURE_ERROR_NO_SIGNATURES 132 
#define  PDF_SIGNATURE_ERROR_OKAY 131 
#define  PDF_SIGNATURE_ERROR_SELF_SIGNED 130 
#define  PDF_SIGNATURE_ERROR_SELF_SIGNED_IN_CHAIN 129 
#define  PDF_SIGNATURE_ERROR_UNKNOWN 128 

char *pdf_signature_error_description(enum pdf_signature_error err)
{
	switch (err)
	{
	case PDF_SIGNATURE_ERROR_OKAY:
		return "";
	case PDF_SIGNATURE_ERROR_NO_SIGNATURES:
		return "No signatures.";
	case PDF_SIGNATURE_ERROR_NO_CERTIFICATE:
		return "No certificate.";
	case PDF_SIGNATURE_ERROR_DIGEST_FAILURE:
		return "Signature invalidated by change to document.";
	case PDF_SIGNATURE_ERROR_SELF_SIGNED:
		return "Self-signed certificate.";
	case PDF_SIGNATURE_ERROR_SELF_SIGNED_IN_CHAIN:
		return "Self-signed certificate in chain.";
	case PDF_SIGNATURE_ERROR_NOT_TRUSTED:
		return "Certificate not trusted.";
	default:
	case PDF_SIGNATURE_ERROR_UNKNOWN:
		return "Unknown error.";
	}
}