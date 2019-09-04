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
typedef  scalar_t__ HCERTSTORE ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_STORE_CREATE_NEW_FLAG ; 
 int /*<<< orphan*/  CERT_STORE_PROV_MEMORY ; 
 scalar_t__ CertOpenStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  add_ms_root_certs (scalar_t__) ; 
 int /*<<< orphan*/  read_trusted_roots_from_known_locations (scalar_t__) ; 

__attribute__((used)) static HCERTSTORE create_root_store(void)
{
#ifdef __REACTOS__
    HCERTSTORE root = NULL;
#endif
    HCERTSTORE memStore = CertOpenStore(CERT_STORE_PROV_MEMORY,
     X509_ASN_ENCODING, 0, CERT_STORE_CREATE_NEW_FLAG, NULL);

    if (memStore)
    {
#ifdef __REACTOS__
        HCERTSTORE regStore;
        CERT_STORE_PROV_INFO provInfo = {
         sizeof(CERT_STORE_PROV_INFO),
         sizeof(rootProvFuncs) / sizeof(rootProvFuncs[0]),
         rootProvFuncs,
         NULL,
         0,
         NULL
        };
#endif

        read_trusted_roots_from_known_locations(memStore);
        add_ms_root_certs(memStore);
#ifdef __REACTOS__
        root = CRYPT_ProvCreateStore(0, memStore, &provInfo);
        regStore = CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, 0, CERT_SYSTEM_STORE_LOCAL_MACHINE, L"AuthRoot");
        if (regStore)
        {
            HCERTSTORE collStore = CertOpenStore(CERT_STORE_PROV_COLLECTION, 0, 0,
                CERT_STORE_CREATE_NEW_FLAG, NULL);
            CertAddStoreToCollection(collStore, regStore, 0, 0);
            CertAddStoreToCollection(collStore, root, 0, 0);
            root = collStore;
        }
#endif
    }
#ifdef __REACTOS__
    TRACE("returning %p\n", root);
    return root;
#else
    TRACE("returning %p\n", memStore);
    return memStore;
#endif
}