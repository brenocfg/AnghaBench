#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  sd_device ;
struct TYPE_2__ {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 
 TYPE_1__ HASH_KEY ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ *,char*,char const*) ; 
 int log_device_debug_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int,char const*,size_t) ; 
 char* net_get_name_persistent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newa (int,size_t) ; 
 int /*<<< orphan*/  sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 int sd_id128_get_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siphash24 (int,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int uint8_t ; 
 int v ; 

int net_get_unique_predictable_data(sd_device *device, bool use_sysname, uint64_t *result) {
        size_t l, sz = 0;
        const char *name;
        int r;
        uint8_t *v;

        assert(device);

        /* net_get_name_persistent() will return one of the device names based on stable information about
         * the device. If this is not available, we fall back to using the actual device name. */
        name = net_get_name_persistent(device);
        if (!name && use_sysname)
                (void) sd_device_get_sysname(device, &name);
        if (!name)
                return log_device_debug_errno(device, SYNTHETIC_ERRNO(ENODATA),
                                              "No stable identifying information found");

        log_device_debug(device, "Using \"%s\" as stable identifying information", name);
        l = strlen(name);
        sz = sizeof(sd_id128_t) + l;
        v = newa(uint8_t, sz);

        /* Fetch some persistent data unique to this machine */
        r = sd_id128_get_machine((sd_id128_t*) v);
        if (r < 0)
                 return r;
        memcpy(v + sizeof(sd_id128_t), name, l);

        /* Let's hash the machine ID plus the device name. We use
         * a fixed, but originally randomly created hash key here. */
        *result = htole64(siphash24(v, sz, HASH_KEY.bytes));
        return 0;
}