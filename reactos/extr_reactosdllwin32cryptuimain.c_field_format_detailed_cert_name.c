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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  PCERT_NAME_BLOB ;
typedef  int DWORD ;

/* Variables and functions */
 int CERT_NAME_STR_CRLF_FLAG ; 
 int CERT_X500_NAME_STR ; 
 int CertNameToStrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static WCHAR *field_format_detailed_cert_name(PCERT_NAME_BLOB name)
{
    WCHAR *str = NULL;
    DWORD len = CertNameToStrW(X509_ASN_ENCODING, name,
     CERT_X500_NAME_STR | CERT_NAME_STR_CRLF_FLAG, NULL, 0);

    if (len)
    {
        str = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
        if (str)
            CertNameToStrW(X509_ASN_ENCODING, name,
             CERT_X500_NAME_STR | CERT_NAME_STR_CRLF_FLAG, str, len);
    }
    return str;
}