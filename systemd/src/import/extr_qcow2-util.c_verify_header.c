#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ incompatible_features; } ;
typedef  TYPE_1__ Header ;

/* Variables and functions */
 int EBADMSG ; 
 int EOPNOTSUPP ; 
 int HEADER_CLUSTER_BITS (TYPE_1__ const*) ; 
 int HEADER_CLUSTER_SIZE (TYPE_1__ const*) ; 
 scalar_t__ HEADER_CRYPT_METHOD (TYPE_1__ const*) ; 
 int HEADER_HEADER_LENGTH (TYPE_1__ const*) ; 
 int HEADER_L1_SIZE (TYPE_1__ const*) ; 
 scalar_t__ HEADER_MAGIC (TYPE_1__ const*) ; 
 int HEADER_SIZE (TYPE_1__ const*) ; 
 int HEADER_VERSION (TYPE_1__ const*) ; 
 int /*<<< orphan*/  IN_SET (int,int,int) ; 
 scalar_t__ QCOW2_MAGIC ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 

__attribute__((used)) static int verify_header(const Header *header) {
        assert(header);

        if (HEADER_MAGIC(header) != QCOW2_MAGIC)
                return -EBADMSG;

        if (!IN_SET(HEADER_VERSION(header), 2, 3))
                return -EOPNOTSUPP;

        if (HEADER_CRYPT_METHOD(header) != 0)
                return -EOPNOTSUPP;

        if (HEADER_CLUSTER_BITS(header) < 9) /* 512K */
                return -EBADMSG;

        if (HEADER_CLUSTER_BITS(header) > 21) /* 2MB */
                return -EBADMSG;

        if (HEADER_SIZE(header) % HEADER_CLUSTER_SIZE(header) != 0)
                return -EBADMSG;

        if (HEADER_L1_SIZE(header) > 32*1024*1024) /* 32MB */
                return -EBADMSG;

        if (HEADER_VERSION(header) == 3) {

                if (header->incompatible_features != 0)
                        return -EOPNOTSUPP;

                if (HEADER_HEADER_LENGTH(header) < sizeof(Header))
                        return -EBADMSG;
        }

        return 0;
}