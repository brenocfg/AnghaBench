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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_5__ {TYPE_1__ Value; int /*<<< orphan*/  pszObjId; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CERT_EXTENSION ;

/* Variables and functions */
 scalar_t__ CryptFormatObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

__attribute__((used)) static WCHAR *crypt_format_extension(const CERT_EXTENSION *ext, DWORD formatStrType)
{
    WCHAR *str = NULL;
    DWORD size;

    if (CryptFormatObject(X509_ASN_ENCODING, 0, formatStrType, NULL,
     ext->pszObjId, ext->Value.pbData, ext->Value.cbData, NULL, &size))
    {
        str = HeapAlloc(GetProcessHeap(), 0, size);
        CryptFormatObject(X509_ASN_ENCODING, 0, formatStrType, NULL,
         ext->pszObjId, ext->Value.pbData, ext->Value.cbData, str, &size);
    }
    return str;
}