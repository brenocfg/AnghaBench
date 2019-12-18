#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_3__ {char* member_0; int const member_1; int const member_2; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
typedef  TYPE_1__ Verb ;

/* Variables and functions */
#define  VERB_ANY 148 
#define  VERB_DEFAULT 147 
 int dispatch_verb (int,char**,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
#define  flush_caches 146 
#define  reset_server_features 145 
#define  reset_statistics 144 
#define  show_statistics 143 
#define  verb_default_route 142 
#define  verb_dns 141 
#define  verb_dns_over_tls 140 
#define  verb_dnssec 139 
#define  verb_domain 138 
#define  verb_help 137 
#define  verb_llmnr 136 
#define  verb_mdns 135 
#define  verb_nta 134 
#define  verb_openpgp 133 
#define  verb_query 132 
#define  verb_revert_link 131 
#define  verb_service 130 
#define  verb_status 129 
#define  verb_tlsa 128 

__attribute__((used)) static int native_main(int argc, char *argv[], sd_bus *bus) {

        static const Verb verbs[] = {
                { "help",                  VERB_ANY, VERB_ANY, 0,            verb_help             },
                { "status",                VERB_ANY, VERB_ANY, VERB_DEFAULT, verb_status           },
                { "query",                 2,        VERB_ANY, 0,            verb_query            },
                { "service",               2,        4,        0,            verb_service          },
                { "openpgp",               2,        VERB_ANY, 0,            verb_openpgp          },
                { "tlsa",                  2,        VERB_ANY, 0,            verb_tlsa             },
                { "statistics",            VERB_ANY, 1,        0,            show_statistics       },
                { "reset-statistics",      VERB_ANY, 1,        0,            reset_statistics      },
                { "flush-caches",          VERB_ANY, 1,        0,            flush_caches          },
                { "reset-server-features", VERB_ANY, 1,        0,            reset_server_features },
                { "dns",                   VERB_ANY, VERB_ANY, 0,            verb_dns              },
                { "domain",                VERB_ANY, VERB_ANY, 0,            verb_domain           },
                { "default-route",         VERB_ANY, 3,        0,            verb_default_route    },
                { "llmnr",                 VERB_ANY, 3,        0,            verb_llmnr            },
                { "mdns",                  VERB_ANY, 3,        0,            verb_mdns             },
                { "dnsovertls",            VERB_ANY, 3,        0,            verb_dns_over_tls     },
                { "dnssec",                VERB_ANY, 3,        0,            verb_dnssec           },
                { "nta",                   VERB_ANY, VERB_ANY, 0,            verb_nta              },
                { "revert",                VERB_ANY, 2,        0,            verb_revert_link      },
                {}
        };

        return dispatch_verb(argc, argv, verbs, bus);
}