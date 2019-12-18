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
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 int utf8_encoded_valid_unichar (char const*,size_t) ; 
 int /*<<< orphan*/  whitelisted_char_for_devnode (char const,int /*<<< orphan*/ *) ; 

int encode_devnode_name(const char *str, char *str_enc, size_t len) {
        size_t i, j;

        if (!str || !str_enc)
                return -EINVAL;

        for (i = 0, j = 0; str[i] != '\0'; i++) {
                int seqlen;

                seqlen = utf8_encoded_valid_unichar(str + i, (size_t) -1);
                if (seqlen > 1) {

                        if (len-j < (size_t)seqlen)
                                return -EINVAL;

                        memcpy(&str_enc[j], &str[i], seqlen);
                        j += seqlen;
                        i += (seqlen-1);

                } else if (str[i] == '\\' || !whitelisted_char_for_devnode(str[i], NULL)) {

                        if (len-j < 4)
                                return -EINVAL;

                        sprintf(&str_enc[j], "\\x%02x", (unsigned char) str[i]);
                        j += 4;

                } else {
                        if (len-j < 1)
                                return -EINVAL;

                        str_enc[j] = str[i];
                        j++;
                }
        }

        if (len-j < 1)
                return -EINVAL;

        str_enc[j] = '\0';
        return 0;
}