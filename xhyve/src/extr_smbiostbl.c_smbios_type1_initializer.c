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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_char ;
struct smbios_table_type1 {int /*<<< orphan*/  uuid; } ;
struct smbios_structure {int dummy; } ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  CC_SHA256_CTX ;

/* Variables and functions */
 int CC_SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  CC_SHA256_Final (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CC_SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CC_SHA256_Update (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int MAXHOSTNAMELEN ; 
 scalar_t__ gethostname (char*,int) ; 
 int /*<<< orphan*/ * guest_uuid_str ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  smbios_generic_initializer (struct smbios_structure*,char const**,char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  uuid_enc_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_from_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ uuid_s_ok ; 
 char* vmname ; 

__attribute__((used)) static int
smbios_type1_initializer(struct smbios_structure *template_entry,
    const char **template_strings, char *curaddr, char **endaddr,
    uint16_t *n, uint16_t *size)
{
	struct smbios_table_type1 *type1;

	smbios_generic_initializer(template_entry, template_strings,
	    curaddr, endaddr, n, size);
	type1 = (struct smbios_table_type1 *)curaddr;

	if (guest_uuid_str != NULL) {
		uuid_t		uuid;
		uint32_t	status;

		uuid_from_string(guest_uuid_str, &uuid, &status);
		if (status != uuid_s_ok)
			return (-1);

		uuid_enc_le(&type1->uuid, &uuid);
	} else {
		CC_SHA256_CTX	mdctx;
		u_char		digest[CC_SHA256_DIGEST_LENGTH];
		char		hostname[MAXHOSTNAMELEN];

		/*
		 * Universally unique and yet reproducible are an
		 * oxymoron, however reproducible is desirable in
		 * this case.
		 */
		if (gethostname(hostname, sizeof(hostname)))
			return (-1);

		CC_SHA256_Init(&mdctx);
		CC_SHA256_Update(&mdctx, vmname, ((unsigned) strlen(vmname)));
		CC_SHA256_Update(&mdctx, hostname, ((unsigned) sizeof(hostname)));
		CC_SHA256_Final(digest, &mdctx);

		/*
		 * Set the variant and version number.
		 */
		digest[6] &= 0x0F;
		digest[6] |= 0x30;	/* version 3 */
		digest[8] &= 0x3F;
		digest[8] |= 0x80;

		memcpy(&type1->uuid, digest, sizeof (digest));
	}

	return (0);
}