#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cbSize; int cChain; scalar_t__ dwRevocationFreshnessTime; void* fHasRevocationFreshnessTime; int /*<<< orphan*/ * rgpLowerQualityChainContext; scalar_t__ cLowerQualityChainContext; TYPE_2__** rgpChain; int /*<<< orphan*/  TrustStatus; } ;
struct TYPE_13__ {int ref; TYPE_1__ context; int /*<<< orphan*/  world; } ;
struct TYPE_12__ {int /*<<< orphan*/  hWorld; } ;
struct TYPE_11__ {int /*<<< orphan*/  TrustStatus; } ;
typedef  TYPE_2__* PCERT_SIMPLE_CHAIN ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  LPFILETIME ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_3__ CertificateChainEngine ;
typedef  TYPE_4__ CertificateChain ;
typedef  int /*<<< orphan*/  CERT_CHAIN_CONTEXT ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_COLLECTION ; 
 int /*<<< orphan*/  CRYPT_FreeSimpleChain (TYPE_2__*) ; 
 void* CRYPT_GetSimpleChainForCert (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  CertAddStoreToCollection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* CryptMemAlloc (int) ; 
 void* FALSE ; 

__attribute__((used)) static BOOL CRYPT_BuildCandidateChainFromCert(CertificateChainEngine *engine,
 PCCERT_CONTEXT cert, LPFILETIME pTime, HCERTSTORE hAdditionalStore, DWORD flags,
 CertificateChain **ppChain)
{
    PCERT_SIMPLE_CHAIN simpleChain = NULL;
    HCERTSTORE world;
    BOOL ret;

    world = CertOpenStore(CERT_STORE_PROV_COLLECTION, 0, 0,
     CERT_STORE_CREATE_NEW_FLAG, NULL);
    CertAddStoreToCollection(world, engine->hWorld, 0, 0);
    if (hAdditionalStore)
        CertAddStoreToCollection(world, hAdditionalStore, 0, 0);
    /* FIXME: only simple chains are supported for now, as CTLs aren't
     * supported yet.
     */
    if ((ret = CRYPT_GetSimpleChainForCert(engine, world, cert, pTime, flags, &simpleChain)))
    {
        CertificateChain *chain = CryptMemAlloc(sizeof(CertificateChain));

        if (chain)
        {
            chain->ref = 1;
            chain->world = world;
            chain->context.cbSize = sizeof(CERT_CHAIN_CONTEXT);
            chain->context.TrustStatus = simpleChain->TrustStatus;
            chain->context.cChain = 1;
            chain->context.rgpChain = CryptMemAlloc(sizeof(PCERT_SIMPLE_CHAIN));
            chain->context.rgpChain[0] = simpleChain;
            chain->context.cLowerQualityChainContext = 0;
            chain->context.rgpLowerQualityChainContext = NULL;
            chain->context.fHasRevocationFreshnessTime = FALSE;
            chain->context.dwRevocationFreshnessTime = 0;
        }
        else
        {
            CRYPT_FreeSimpleChain(simpleChain);
            ret = FALSE;
        }
        *ppChain = chain;
    }
    return ret;
}