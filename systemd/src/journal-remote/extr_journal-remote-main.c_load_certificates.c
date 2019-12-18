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

/* Variables and functions */
 int /*<<< orphan*/  CERT_FILE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PRIV_KEY_FILE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUST_FILE ; 
 scalar_t__ arg_cert ; 
 scalar_t__ arg_key ; 
 scalar_t__ arg_listen_http ; 
 scalar_t__ arg_listen_raw ; 
 scalar_t__ arg_trust ; 
 scalar_t__ arg_trust_all ; 
 int log_error_errno (int,char*,...) ; 
 int /*<<< orphan*/  log_info (char*) ; 
 int read_full_file (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_certificates(char **key, char **cert, char **trust) {
        int r;

        r = read_full_file(arg_key ?: PRIV_KEY_FILE, key, NULL);
        if (r < 0)
                return log_error_errno(r, "Failed to read key from file '%s': %m",
                                       arg_key ?: PRIV_KEY_FILE);

        r = read_full_file(arg_cert ?: CERT_FILE, cert, NULL);
        if (r < 0)
                return log_error_errno(r, "Failed to read certificate from file '%s': %m",
                                       arg_cert ?: CERT_FILE);

        if (arg_trust_all)
                log_info("Certificate checking disabled.");
        else {
                r = read_full_file(arg_trust ?: TRUST_FILE, trust, NULL);
                if (r < 0)
                        return log_error_errno(r, "Failed to read CA certificate file '%s': %m",
                                               arg_trust ?: TRUST_FILE);
        }

        if ((arg_listen_raw || arg_listen_http) && *trust)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Option --trust makes all non-HTTPS connections untrusted.");

        return 0;
}