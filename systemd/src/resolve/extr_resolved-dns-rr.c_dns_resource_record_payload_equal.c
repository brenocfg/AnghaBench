#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_29__ {int /*<<< orphan*/  os; int /*<<< orphan*/  cpu; } ;
struct TYPE_28__ {int /*<<< orphan*/  name; } ;
struct TYPE_27__ {int /*<<< orphan*/  port; int /*<<< orphan*/  weight; int /*<<< orphan*/  priority; int /*<<< orphan*/  name; } ;
struct TYPE_26__ {int type; } ;
struct TYPE_25__ {int /*<<< orphan*/  types; int /*<<< orphan*/  next_domain_name; } ;
struct TYPE_24__ {int /*<<< orphan*/  altitude; int /*<<< orphan*/  longitude; int /*<<< orphan*/  latitude; int /*<<< orphan*/  vert_pre; int /*<<< orphan*/  horiz_pre; int /*<<< orphan*/  size; int /*<<< orphan*/  version; } ;
struct TYPE_23__ {int /*<<< orphan*/  exchange; int /*<<< orphan*/  priority; } ;
struct TYPE_22__ {int /*<<< orphan*/  minimum; int /*<<< orphan*/  expire; int /*<<< orphan*/  retry; int /*<<< orphan*/  refresh; int /*<<< orphan*/  serial; int /*<<< orphan*/  rname; int /*<<< orphan*/  mname; } ;
struct TYPE_21__ {int /*<<< orphan*/  in6_addr; } ;
struct TYPE_20__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  flags; int /*<<< orphan*/  matching_type; int /*<<< orphan*/  selector; int /*<<< orphan*/  cert_usage; int /*<<< orphan*/  types; int /*<<< orphan*/  iterations; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  signer; int /*<<< orphan*/  key_tag; int /*<<< orphan*/  inception; int /*<<< orphan*/  expiration; int /*<<< orphan*/  original_ttl; int /*<<< orphan*/  labels; int /*<<< orphan*/  type_covered; int /*<<< orphan*/  protocol; int /*<<< orphan*/  fptype; int /*<<< orphan*/  digest_type; } ;
struct TYPE_18__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  items; } ;
struct TYPE_19__ {scalar_t__ unparseable; TYPE_15__ generic; TYPE_15__ caa; TYPE_15__ tlsa; TYPE_15__ nsec3; TYPE_5__ nsec; TYPE_15__ rrsig; TYPE_15__ dnskey; TYPE_15__ sshfp; TYPE_15__ ds; TYPE_4__ loc; TYPE_3__ mx; TYPE_2__ soa; TYPE_1__ aaaa; TYPE_11__ a; TYPE_10__ txt; TYPE_9__ hinfo; TYPE_8__ ptr; TYPE_7__ srv; TYPE_6__* key; } ;
typedef  TYPE_12__ DnsResourceRecord ;

/* Variables and functions */
#define  DNS_TYPE_A 149 
#define  DNS_TYPE_AAAA 148 
#define  DNS_TYPE_CAA 147 
#define  DNS_TYPE_CNAME 146 
#define  DNS_TYPE_DNAME 145 
#define  DNS_TYPE_DNSKEY 144 
#define  DNS_TYPE_DS 143 
#define  DNS_TYPE_HINFO 142 
#define  DNS_TYPE_LOC 141 
#define  DNS_TYPE_MX 140 
#define  DNS_TYPE_NS 139 
#define  DNS_TYPE_NSEC 138 
#define  DNS_TYPE_NSEC3 137 
#define  DNS_TYPE_OPENPGPKEY 136 
#define  DNS_TYPE_PTR 135 
#define  DNS_TYPE_RRSIG 134 
#define  DNS_TYPE_SOA 133 
#define  DNS_TYPE_SPF 132 
#define  DNS_TYPE_SRV 131 
#define  DNS_TYPE_SSHFP 130 
#define  DNS_TYPE_TLSA 129 
#define  DNS_TYPE_TXT 128 
 int FIELD_EQUAL (TYPE_15__,TYPE_15__,int /*<<< orphan*/ ) ; 
 int _DNS_TYPE_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bitmap_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  digest ; 
 int dns_name_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dns_txt_item_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fingerprint ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  next_hashed_name ; 
 int /*<<< orphan*/  salt ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  strcaseeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value ; 

int dns_resource_record_payload_equal(const DnsResourceRecord *a, const DnsResourceRecord *b) {
        int r;

        /* Check if a and b are the same, but don't look at their keys */

        if (a->unparseable != b->unparseable)
                return 0;

        switch (a->unparseable ? _DNS_TYPE_INVALID : a->key->type) {

        case DNS_TYPE_SRV:
                r = dns_name_equal(a->srv.name, b->srv.name);
                if (r <= 0)
                        return r;

                return a->srv.priority == b->srv.priority &&
                       a->srv.weight == b->srv.weight &&
                       a->srv.port == b->srv.port;

        case DNS_TYPE_PTR:
        case DNS_TYPE_NS:
        case DNS_TYPE_CNAME:
        case DNS_TYPE_DNAME:
                return dns_name_equal(a->ptr.name, b->ptr.name);

        case DNS_TYPE_HINFO:
                return strcaseeq(a->hinfo.cpu, b->hinfo.cpu) &&
                       strcaseeq(a->hinfo.os, b->hinfo.os);

        case DNS_TYPE_SPF: /* exactly the same as TXT */
        case DNS_TYPE_TXT:
                return dns_txt_item_equal(a->txt.items, b->txt.items);

        case DNS_TYPE_A:
                return memcmp(&a->a.in_addr, &b->a.in_addr, sizeof(struct in_addr)) == 0;

        case DNS_TYPE_AAAA:
                return memcmp(&a->aaaa.in6_addr, &b->aaaa.in6_addr, sizeof(struct in6_addr)) == 0;

        case DNS_TYPE_SOA:
                r = dns_name_equal(a->soa.mname, b->soa.mname);
                if (r <= 0)
                        return r;
                r = dns_name_equal(a->soa.rname, b->soa.rname);
                if (r <= 0)
                        return r;

                return a->soa.serial  == b->soa.serial &&
                       a->soa.refresh == b->soa.refresh &&
                       a->soa.retry   == b->soa.retry &&
                       a->soa.expire  == b->soa.expire &&
                       a->soa.minimum == b->soa.minimum;

        case DNS_TYPE_MX:
                if (a->mx.priority != b->mx.priority)
                        return 0;

                return dns_name_equal(a->mx.exchange, b->mx.exchange);

        case DNS_TYPE_LOC:
                assert(a->loc.version == b->loc.version);

                return a->loc.size == b->loc.size &&
                       a->loc.horiz_pre == b->loc.horiz_pre &&
                       a->loc.vert_pre == b->loc.vert_pre &&
                       a->loc.latitude == b->loc.latitude &&
                       a->loc.longitude == b->loc.longitude &&
                       a->loc.altitude == b->loc.altitude;

        case DNS_TYPE_DS:
                return a->ds.key_tag == b->ds.key_tag &&
                       a->ds.algorithm == b->ds.algorithm &&
                       a->ds.digest_type == b->ds.digest_type &&
                       FIELD_EQUAL(a->ds, b->ds, digest);

        case DNS_TYPE_SSHFP:
                return a->sshfp.algorithm == b->sshfp.algorithm &&
                       a->sshfp.fptype == b->sshfp.fptype &&
                       FIELD_EQUAL(a->sshfp, b->sshfp, fingerprint);

        case DNS_TYPE_DNSKEY:
                return a->dnskey.flags == b->dnskey.flags &&
                       a->dnskey.protocol == b->dnskey.protocol &&
                       a->dnskey.algorithm == b->dnskey.algorithm &&
                       FIELD_EQUAL(a->dnskey, b->dnskey, key);

        case DNS_TYPE_RRSIG:
                /* do the fast comparisons first */
                return a->rrsig.type_covered == b->rrsig.type_covered &&
                       a->rrsig.algorithm == b->rrsig.algorithm &&
                       a->rrsig.labels == b->rrsig.labels &&
                       a->rrsig.original_ttl == b->rrsig.original_ttl &&
                       a->rrsig.expiration == b->rrsig.expiration &&
                       a->rrsig.inception == b->rrsig.inception &&
                       a->rrsig.key_tag == b->rrsig.key_tag &&
                       FIELD_EQUAL(a->rrsig, b->rrsig, signature) &&
                       dns_name_equal(a->rrsig.signer, b->rrsig.signer);

        case DNS_TYPE_NSEC:
                return dns_name_equal(a->nsec.next_domain_name, b->nsec.next_domain_name) &&
                       bitmap_equal(a->nsec.types, b->nsec.types);

        case DNS_TYPE_NSEC3:
                return a->nsec3.algorithm == b->nsec3.algorithm &&
                       a->nsec3.flags == b->nsec3.flags &&
                       a->nsec3.iterations == b->nsec3.iterations &&
                       FIELD_EQUAL(a->nsec3, b->nsec3, salt) &&
                       FIELD_EQUAL(a->nsec3, b->nsec3, next_hashed_name) &&
                       bitmap_equal(a->nsec3.types, b->nsec3.types);

        case DNS_TYPE_TLSA:
                return a->tlsa.cert_usage == b->tlsa.cert_usage &&
                       a->tlsa.selector == b->tlsa.selector &&
                       a->tlsa.matching_type == b->tlsa.matching_type &&
                       FIELD_EQUAL(a->tlsa, b->tlsa, data);

        case DNS_TYPE_CAA:
                return a->caa.flags == b->caa.flags &&
                       streq(a->caa.tag, b->caa.tag) &&
                       FIELD_EQUAL(a->caa, b->caa, value);

        case DNS_TYPE_OPENPGPKEY:
        default:
                return FIELD_EQUAL(a->generic, b->generic, data);
        }
}