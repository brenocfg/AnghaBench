#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nd_router_advert {scalar_t__ nd_ra_type; scalar_t__ nd_ra_code; int nd_ra_flags_reserved; int /*<<< orphan*/  nd_ra_router_lifetime; int /*<<< orphan*/  nd_ra_curhoplimit; } ;
struct TYPE_5__ {int raw_size; int flags; int preference; int rindex; int /*<<< orphan*/  mtu; int /*<<< orphan*/  lifetime; int /*<<< orphan*/  hop_limit; } ;
typedef  TYPE_1__ sd_ndisc_router ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPV6_MIN_MTU ; 
 struct nd_router_advert* NDISC_ROUTER_RAW (TYPE_1__*) ; 
 scalar_t__ ND_ROUTER_ADVERT ; 
#define  SD_NDISC_OPTION_DNSSL 133 
#define  SD_NDISC_OPTION_FLAGS_EXTENSION 132 
#define  SD_NDISC_OPTION_MTU 131 
#define  SD_NDISC_OPTION_PREFIX_INFORMATION 130 
#define  SD_NDISC_OPTION_RDNSS 129 
#define  SD_NDISC_OPTION_ROUTE_INFORMATION 128 
 int /*<<< orphan*/  SD_NDISC_PREFERENCE_HIGH ; 
 int /*<<< orphan*/  SD_NDISC_PREFERENCE_LOW ; 
 int SD_NDISC_PREFERENCE_MEDIUM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_ndisc (char*) ; 

int ndisc_router_parse(sd_ndisc_router *rt) {
        struct nd_router_advert *a;
        const uint8_t *p;
        bool has_mtu = false, has_flag_extension = false;
        size_t left;

        assert(rt);

        if (rt->raw_size < sizeof(struct nd_router_advert)) {
                log_ndisc("Too small to be a router advertisement, ignoring.");
                return -EBADMSG;
        }

        /* Router advertisement packets are neatly aligned to 64bit boundaries, hence we can access them directly */
        a = NDISC_ROUTER_RAW(rt);

        if (a->nd_ra_type != ND_ROUTER_ADVERT) {
                log_ndisc("Received ND packet that is not a router advertisement, ignoring.");
                return -EBADMSG;
        }

        if (a->nd_ra_code != 0) {
                log_ndisc("Received ND packet with wrong RA code, ignoring.");
                return -EBADMSG;
        }

        rt->hop_limit = a->nd_ra_curhoplimit;
        rt->flags = a->nd_ra_flags_reserved; /* the first 8bit */
        rt->lifetime = be16toh(a->nd_ra_router_lifetime);

        rt->preference = (rt->flags >> 3) & 3;
        if (!IN_SET(rt->preference, SD_NDISC_PREFERENCE_LOW, SD_NDISC_PREFERENCE_HIGH))
                rt->preference = SD_NDISC_PREFERENCE_MEDIUM;

        p = (const uint8_t*) NDISC_ROUTER_RAW(rt) + sizeof(struct nd_router_advert);
        left = rt->raw_size - sizeof(struct nd_router_advert);

        for (;;) {
                uint8_t type;
                size_t length;

                if (left == 0)
                        break;

                if (left < 2) {
                        log_ndisc("Option lacks header, ignoring datagram.");
                        return -EBADMSG;
                }

                type = p[0];
                length = p[1] * 8;

                if (length == 0) {
                        log_ndisc("Zero-length option, ignoring datagram.");
                        return -EBADMSG;
                }
                if (left < length) {
                        log_ndisc("Option truncated, ignoring datagram.");
                        return -EBADMSG;
                }

                switch (type) {

                case SD_NDISC_OPTION_PREFIX_INFORMATION:

                        if (length != 4*8) {
                                log_ndisc("Prefix option of invalid size, ignoring datagram.");
                                return -EBADMSG;
                        }

                        if (p[2] > 128) {
                                log_ndisc("Bad prefix length, ignoring datagram.");
                                return -EBADMSG;
                        }

                        break;

                case SD_NDISC_OPTION_MTU: {
                        uint32_t m;

                        if (has_mtu) {
                                log_ndisc("MTU option specified twice, ignoring.");
                                break;
                        }

                        if (length != 8) {
                                log_ndisc("MTU option of invalid size, ignoring datagram.");
                                return -EBADMSG;
                        }

                        m = be32toh(*(uint32_t*) (p + 4));
                        if (m >= IPV6_MIN_MTU) /* ignore invalidly small MTUs */
                                rt->mtu = m;

                        has_mtu = true;
                        break;
                }

                case SD_NDISC_OPTION_ROUTE_INFORMATION:
                        if (length < 1*8 || length > 3*8) {
                                log_ndisc("Route information option of invalid size, ignoring datagram.");
                                return -EBADMSG;
                        }

                        if (p[2] > 128) {
                                log_ndisc("Bad route prefix length, ignoring datagram.");
                                return -EBADMSG;
                        }

                        break;

                case SD_NDISC_OPTION_RDNSS:
                        if (length < 3*8 || (length % (2*8)) != 1*8) {
                                log_ndisc("RDNSS option has invalid size.");
                                return -EBADMSG;
                        }

                        break;

                case SD_NDISC_OPTION_FLAGS_EXTENSION:

                        if (has_flag_extension) {
                                log_ndisc("Flags extension option specified twice, ignoring.");
                                break;
                        }

                        if (length < 1*8) {
                                log_ndisc("Flags extension option has invalid size.");
                                return -EBADMSG;
                        }

                        /* Add in the additional flags bits */
                        rt->flags |=
                                ((uint64_t) p[2] << 8) |
                                ((uint64_t) p[3] << 16) |
                                ((uint64_t) p[4] << 24) |
                                ((uint64_t) p[5] << 32) |
                                ((uint64_t) p[6] << 40) |
                                ((uint64_t) p[7] << 48);

                        has_flag_extension = true;
                        break;

                case SD_NDISC_OPTION_DNSSL:
                        if (length < 2*8) {
                                log_ndisc("DNSSL option has invalid size.");
                                return -EBADMSG;
                        }

                        break;
                }

                p += length, left -= length;
        }

        rt->rindex = sizeof(struct nd_router_advert);
        return 0;
}