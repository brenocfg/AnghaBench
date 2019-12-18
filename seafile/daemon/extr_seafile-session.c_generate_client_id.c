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
 int /*<<< orphan*/  calculate_sha1 (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char*) ; 
 char* gen_uuid () ; 
 int /*<<< orphan*/  rawdata_to_hex (unsigned char*,char*,int) ; 

__attribute__((used)) static char *
generate_client_id ()
{
    char *uuid = gen_uuid();
    unsigned char buf[20];
    char sha1[41];

    calculate_sha1 (buf, uuid, 20);
    rawdata_to_hex (buf, sha1, 20);

    g_free (uuid);
    return g_strdup(sha1);
}