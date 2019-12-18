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
typedef  int uint32_t ;
typedef  scalar_t__ uid_t ;
typedef  char const Manager ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int DESTROY_IPC_FLAG ; 
 int PTR_TO_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  UINT32_TO_PTR (int) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int hashmap_ensure_allocated (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hashmap_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int /*<<< orphan*/  log_oom () ; 
 int parse_uid (char const*,scalar_t__*) ; 
 int /*<<< orphan*/  trivial_hash_ops ; 

__attribute__((used)) static void manager_deserialize_uid_refs_one_internal(
                Manager *m,
                Hashmap** uid_refs,
                const char *value) {

        uid_t uid;
        uint32_t c;
        int r;

        assert(m);
        assert(uid_refs);
        assert(value);

        r = parse_uid(value, &uid);
        if (r < 0 || uid == 0) {
                log_debug("Unable to parse UID reference serialization");
                return;
        }

        r = hashmap_ensure_allocated(uid_refs, &trivial_hash_ops);
        if (r < 0) {
                log_oom();
                return;
        }

        c = PTR_TO_UINT32(hashmap_get(*uid_refs, UID_TO_PTR(uid)));
        if (c & DESTROY_IPC_FLAG)
                return;

        c |= DESTROY_IPC_FLAG;

        r = hashmap_replace(*uid_refs, UID_TO_PTR(uid), UINT32_TO_PTR(c));
        if (r < 0) {
                log_debug_errno(r, "Failed to add UID reference entry: %m");
                return;
        }
}