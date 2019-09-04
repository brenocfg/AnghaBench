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
struct TYPE_4__ {int /*<<< orphan*/  TrustStatus; } ;
struct TYPE_5__ {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CertificateChain ;

/* Variables and functions */
 int CERT_TRUST_INVALID_BASIC_CONSTRAINTS ; 
 int CERT_TRUST_IS_NOT_SIGNATURE_VALID ; 
 int CERT_TRUST_IS_NOT_TIME_NESTED ; 
 int CERT_TRUST_IS_NOT_TIME_VALID ; 
 int CERT_TRUST_IS_PARTIAL_CHAIN ; 
 int CERT_TRUST_IS_UNTRUSTED_ROOT ; 
 int /*<<< orphan*/  CHAIN_QUALITY_BASIC_CONSTRAINTS ; 
 int /*<<< orphan*/  CHAIN_QUALITY_COMPLETE_CHAIN ; 
 int /*<<< orphan*/  CHAIN_QUALITY_HIGHEST ; 
 int /*<<< orphan*/  CHAIN_QUALITY_SIGNATURE_VALID ; 
 int /*<<< orphan*/  CHAIN_QUALITY_TIME_VALID ; 
 int /*<<< orphan*/  CHAIN_QUALITY_TRUSTED_ROOT ; 
 scalar_t__ IS_TRUST_ERROR_SET (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static DWORD CRYPT_ChainQuality(const CertificateChain *chain)
{
    DWORD quality = CHAIN_QUALITY_HIGHEST;

    if (IS_TRUST_ERROR_SET(&chain->context.TrustStatus,
     CERT_TRUST_IS_UNTRUSTED_ROOT))
        quality &= ~CHAIN_QUALITY_TRUSTED_ROOT;
    if (IS_TRUST_ERROR_SET(&chain->context.TrustStatus,
     CERT_TRUST_INVALID_BASIC_CONSTRAINTS))
        quality &= ~CHAIN_QUALITY_BASIC_CONSTRAINTS;
    if (IS_TRUST_ERROR_SET(&chain->context.TrustStatus,
     CERT_TRUST_IS_PARTIAL_CHAIN))
        quality &= ~CHAIN_QUALITY_COMPLETE_CHAIN;
    if (IS_TRUST_ERROR_SET(&chain->context.TrustStatus,
     CERT_TRUST_IS_NOT_TIME_VALID | CERT_TRUST_IS_NOT_TIME_NESTED))
        quality &= ~CHAIN_QUALITY_TIME_VALID;
    if (IS_TRUST_ERROR_SET(&chain->context.TrustStatus,
     CERT_TRUST_IS_NOT_SIGNATURE_VALID))
        quality &= ~CHAIN_QUALITY_SIGNATURE_VALID;
    return quality;
}