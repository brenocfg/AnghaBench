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
 size_t ELEMENTSOF (size_t*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cescape_char (char const,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ write_ellipsis (char*,int) ; 

char *cellescape(char *buf, size_t len, const char *s) {
        /* Escape and ellipsize s into buffer buf of size len. Only non-control ASCII
         * characters are copied as they are, everything else is escaped. The result
         * is different then if escaping and ellipsization was performed in two
         * separate steps, because each sequence is either stored in full or skipped.
         *
         * This function should be used for logging about strings which expected to
         * be plain ASCII in a safe way.
         *
         * An ellipsis will be used if s is too long. It was always placed at the
         * very end.
         */

        size_t i = 0, last_char_width[4] = {}, k = 0, j;

        assert(len > 0); /* at least a terminating NUL */

        for (;;) {
                char four[4];
                int w;

                if (*s == 0) /* terminating NUL detected? then we are done! */
                        goto done;

                w = cescape_char(*s, four);
                if (i + w + 1 > len) /* This character doesn't fit into the buffer anymore? In that case let's
                                      * ellipsize at the previous location */
                        break;

                /* OK, there was space, let's add this escaped character to the buffer */
                memcpy(buf + i, four, w);
                i += w;

                /* And remember its width in the ring buffer */
                last_char_width[k] = w;
                k = (k + 1) % 4;

                s++;
        }

        /* Ellipsation is necessary. This means we might need to truncate the string again to make space for 4
         * characters ideally, but the buffer is shorter than that in the first place take what we can get */
        for (j = 0; j < ELEMENTSOF(last_char_width); j++) {

                if (i + 4 <= len) /* nice, we reached our space goal */
                        break;

                k = k == 0 ? 3 : k - 1;
                if (last_char_width[k] == 0) /* bummer, we reached the beginning of the strings */
                        break;

                assert(i >= last_char_width[k]);
                i -= last_char_width[k];
        }

        if (i + 4 <= len) /* yay, enough space */
                i += write_ellipsis(buf + i, false);
        else if (i + 3 <= len) { /* only space for ".." */
                buf[i++] = '.';
                buf[i++] = '.';
        } else if (i + 2 <= len) /* only space for a single "." */
                buf[i++] = '.';
        else
                assert(i + 1 <= len);

 done:
        buf[i] = '\0';
        return buf;
}