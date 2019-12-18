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
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ gid_is_valid (scalar_t__) ; 
 scalar_t__ uid_is_valid (scalar_t__) ; 

__attribute__((used)) static bool match_uid_gid(uid_t subject_uid, gid_t subject_gid, uid_t delete_uid, gid_t delete_gid) {

        if (uid_is_valid(delete_uid) && subject_uid == delete_uid)
                return true;

        if (gid_is_valid(delete_gid) && subject_gid == delete_gid)
                return true;

        return false;
}