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
struct DynamicBuffer {int /*<<< orphan*/ * data; int /*<<< orphan*/  used; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_STORE_ADD_NEW ; 
 int /*<<< orphan*/  CRYPT_STRING_BASE64 ; 
 scalar_t__ CertAddEncodedCertificateToStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ CryptStringToBinaryA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int TRUE ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  add_line_to_buffer (struct DynamicBuffer*,char*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_buffer (struct DynamicBuffer*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL import_base64_certs_from_fp(FILE *fp, HCERTSTORE store)
{
    char line[1024];
    BOOL in_cert = FALSE;
    struct DynamicBuffer saved_cert = { 0, 0, NULL };
    int num_certs = 0;

    TRACE("\n");
    while (fgets(line, sizeof(line), fp))
    {
        static const char header[] = "-----BEGIN CERTIFICATE-----";
        static const char trailer[] = "-----END CERTIFICATE-----";

        if (!strncmp(line, header, strlen(header)))
        {
            TRACE("begin new certificate\n");
            in_cert = TRUE;
            reset_buffer(&saved_cert);
        }
        else if (!strncmp(line, trailer, strlen(trailer)))
        {
            DWORD size;

            TRACE("end of certificate, adding cert\n");
            in_cert = FALSE;
            if (CryptStringToBinaryA((char *)saved_cert.data, saved_cert.used,
             CRYPT_STRING_BASE64, NULL, &size, NULL, NULL))
            {
                LPBYTE buf = CryptMemAlloc(size);

                if (buf)
                {
                    CryptStringToBinaryA((char *)saved_cert.data,
                     saved_cert.used, CRYPT_STRING_BASE64, buf, &size, NULL,
                     NULL);
                    if (CertAddEncodedCertificateToStore(store,
                     X509_ASN_ENCODING, buf, size, CERT_STORE_ADD_NEW, NULL))
                        num_certs++;
                    CryptMemFree(buf);
                }
            }
        }
        else if (in_cert)
            add_line_to_buffer(&saved_cert, line);
    }
    CryptMemFree(saved_cert.data);
    TRACE("Read %d certs\n", num_certs);
    return num_certs > 0;
}