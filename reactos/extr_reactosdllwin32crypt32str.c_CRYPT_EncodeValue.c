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
struct X500TokenW {int dummy; } ;
typedef  int /*<<< orphan*/  PCERT_NAME_BLOB ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_EncodeValueWithType (size_t,struct X500TokenW const*,int /*<<< orphan*/ ,size_t const,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 

__attribute__((used)) static BOOL CRYPT_EncodeValue(DWORD dwCertEncodingType,
 const struct X500TokenW *value, PCERT_NAME_BLOB output, const DWORD *types,
 LPCWSTR *ppszError)
{
    DWORD i;
    BOOL ret;

    ret = FALSE;
    for (i = 0; !ret && types[i]; i++)
        ret = CRYPT_EncodeValueWithType(dwCertEncodingType, value, output,
         types[i], ppszError);
    return ret;
}