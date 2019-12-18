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
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {TYPE_1__ dnstls_data; } ;
typedef  TYPE_2__ Manager ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  ERR_load_crypto_strings () ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_set_default_verify_paths (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_min_proto_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_OP_NO_COMPRESSION ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  TLS1_2_VERSION ; 
 int /*<<< orphan*/  TLS_client_method () ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ) ; 

int dnstls_manager_init(Manager *manager) {
        int r;
        assert(manager);

        ERR_load_crypto_strings();
        SSL_load_error_strings();
        manager->dnstls_data.ctx = SSL_CTX_new(TLS_client_method());

        if (!manager->dnstls_data.ctx)
                return -ENOMEM;

        SSL_CTX_set_min_proto_version(manager->dnstls_data.ctx, TLS1_2_VERSION);
        SSL_CTX_set_options(manager->dnstls_data.ctx, SSL_OP_NO_COMPRESSION);
        r = SSL_CTX_set_default_verify_paths(manager->dnstls_data.ctx);
        if (r < 0)
                log_warning("Failed to load system trust store: %s", ERR_error_string(ERR_get_error(), NULL));

        return 0;
}