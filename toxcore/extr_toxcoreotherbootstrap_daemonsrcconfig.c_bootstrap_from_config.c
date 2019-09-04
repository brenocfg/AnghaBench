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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  config_t ;
typedef  int /*<<< orphan*/  config_setting_t ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 scalar_t__ CONFIG_FALSE ; 
 int DHT_bootstrap_from_address (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  LOG_LEVEL_INFO ; 
 int /*<<< orphan*/  LOG_LEVEL_WARNING ; 
 int MAX_ALLOWED_PORT ; 
 int MIN_ALLOWED_PORT ; 
 int /*<<< orphan*/  config_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_error_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_error_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_error_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_lookup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ config_read_file (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * config_setting_get_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ config_setting_length (int /*<<< orphan*/ *) ; 
 scalar_t__ config_setting_lookup_int (int /*<<< orphan*/ *,char const*,int*) ; 
 scalar_t__ config_setting_lookup_string (int /*<<< orphan*/ *,char const*,char const**) ; 
 int /*<<< orphan*/  config_setting_remove_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hex_string_to_bin (char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write_log (int /*<<< orphan*/ ,char*,...) ; 

int bootstrap_from_config(const char *cfg_file_path, DHT *dht, int enable_ipv6)
{
    const char *NAME_BOOTSTRAP_NODES = "bootstrap_nodes";

    const char *NAME_PUBLIC_KEY = "public_key";
    const char *NAME_PORT       = "port";
    const char *NAME_ADDRESS    = "address";

    config_t cfg;

    config_init(&cfg);

    if (config_read_file(&cfg, cfg_file_path) == CONFIG_FALSE) {
        write_log(LOG_LEVEL_ERROR, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return 0;
    }

    config_setting_t *node_list = config_lookup(&cfg, NAME_BOOTSTRAP_NODES);

    if (node_list == NULL) {
        write_log(LOG_LEVEL_WARNING, "No '%s' setting in the configuration file. Skipping bootstrapping.\n",
                  NAME_BOOTSTRAP_NODES);
        config_destroy(&cfg);
        return 1;
    }

    if (config_setting_length(node_list) == 0) {
        write_log(LOG_LEVEL_WARNING, "No bootstrap nodes found. Skipping bootstrapping.\n");
        config_destroy(&cfg);
        return 1;
    }

    int bs_port;
    const char *bs_address;
    const char *bs_public_key;

    config_setting_t *node;

    int i = 0;

    while (config_setting_length(node_list)) {

        node = config_setting_get_elem(node_list, 0);

        if (node == NULL) {
            config_destroy(&cfg);
            return 0;
        }

        // Check that all settings are present
        if (config_setting_lookup_string(node, NAME_PUBLIC_KEY, &bs_public_key) == CONFIG_FALSE) {
            write_log(LOG_LEVEL_WARNING, "Bootstrap node #%d: Couldn't find '%s' setting. Skipping the node.\n", i,
                      NAME_PUBLIC_KEY);
            goto next;
        }

        if (config_setting_lookup_int(node, NAME_PORT, &bs_port) == CONFIG_FALSE) {
            write_log(LOG_LEVEL_WARNING, "Bootstrap node #%d: Couldn't find '%s' setting. Skipping the node.\n", i, NAME_PORT);
            goto next;
        }

        if (config_setting_lookup_string(node, NAME_ADDRESS, &bs_address) == CONFIG_FALSE) {
            write_log(LOG_LEVEL_WARNING, "Bootstrap node #%d: Couldn't find '%s' setting. Skipping the node.\n", i, NAME_ADDRESS);
            goto next;
        }

        // Process settings
        if (strlen(bs_public_key) != crypto_box_PUBLICKEYBYTES * 2) {
            write_log(LOG_LEVEL_WARNING, "Bootstrap node #%d: Invalid '%s': %s. Skipping the node.\n", i, NAME_PUBLIC_KEY,
                      bs_public_key);
            goto next;
        }

        if (bs_port < MIN_ALLOWED_PORT || bs_port > MAX_ALLOWED_PORT) {
            write_log(LOG_LEVEL_WARNING, "Bootstrap node #%d: Invalid '%s': %d, should be in [%d, %d]. Skipping the node.\n", i,
                      NAME_PORT,
                      bs_port, MIN_ALLOWED_PORT, MAX_ALLOWED_PORT);
            goto next;
        }

        uint8_t *bs_public_key_bin = hex_string_to_bin((char *)bs_public_key);
        const int address_resolved = DHT_bootstrap_from_address(dht, bs_address, enable_ipv6, htons(bs_port),
                                     bs_public_key_bin);
        free(bs_public_key_bin);

        if (!address_resolved) {
            write_log(LOG_LEVEL_WARNING, "Bootstrap node #%d: Invalid '%s': %s. Skipping the node.\n", i, NAME_ADDRESS, bs_address);
            goto next;
        }

        write_log(LOG_LEVEL_INFO, "Successfully added bootstrap node #%d: %s:%d %s\n", i, bs_address, bs_port, bs_public_key);

next:
        // config_setting_lookup_string() allocates string inside and doesn't allow us to free it direcly
        // though it's freed when the element is removed, so we free it right away in order to keep memory
        // consumption minimal
        config_setting_remove_elem(node_list, 0);
        i++;
    }

    config_destroy(&cfg);

    return 1;
}