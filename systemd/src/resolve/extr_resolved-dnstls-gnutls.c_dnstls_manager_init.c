#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cert_cred; } ;
struct TYPE_6__ {TYPE_1__ dnstls_data; } ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int gnutls_certificate_set_x509_system_trust (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ) ; 

int dnstls_manager_init(Manager *manager) {
        int r;
        assert(manager);

        r = gnutls_certificate_allocate_credentials(&manager->dnstls_data.cert_cred);
        if (r < 0)
                return -ENOMEM;

        r = gnutls_certificate_set_x509_system_trust(manager->dnstls_data.cert_cred);
        if (r < 0)
                log_warning("Failed to load system trust store: %s", gnutls_strerror(r));

        return 0;
}