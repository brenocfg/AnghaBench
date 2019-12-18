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
typedef  int /*<<< orphan*/  int8_t ;
typedef  enum strncpy_pad_check { ____Placeholder_strncpy_pad_check } strncpy_pad_check ;

/* Variables and functions */
#define  ISO9660_7BIT 131 
#define  ISO9660_ACHARS 130 
#define  ISO9660_DCHARS 129 
#define  ISO9660_NOCHECK 128 
 int /*<<< orphan*/  cdio_assert (int) ; 
 int /*<<< orphan*/  cdio_assert_not_reached () ; 
 int /*<<< orphan*/  cdio_warn (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  iso9660_is_achar (char const) ; 
 int /*<<< orphan*/  iso9660_is_dchar (char const) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char *
iso9660_strncpy_pad(char dst[], const char src[], size_t len,
                    enum strncpy_pad_check _check)
{
  size_t rlen;

  cdio_assert (dst != NULL);
  cdio_assert (src != NULL);
  cdio_assert (len > 0);

  switch (_check)
    {
      int idx;
    case ISO9660_NOCHECK:
      break;

    case ISO9660_7BIT:
      for (idx = 0; src[idx]; idx++)
        if ((int8_t) src[idx] < 0)
          {
            cdio_warn ("string '%s' fails 7bit constraint (pos = %d)",
                      src, idx);
            break;
          }
      break;

    case ISO9660_ACHARS:
      for (idx = 0; src[idx]; idx++)
        if (!iso9660_is_achar (src[idx]))
          {
            cdio_warn ("string '%s' fails a-character constraint (pos = %d)",
                      src, idx);
            break;
          }
      break;

    case ISO9660_DCHARS:
      for (idx = 0; src[idx]; idx++)
        if (!iso9660_is_dchar (src[idx]))
          {
            cdio_warn ("string '%s' fails d-character constraint (pos = %d)",
                      src, idx);
            break;
          }
      break;

    default:
      cdio_assert_not_reached ();
      break;
    }

  rlen = strlen (src);

  if (rlen > len)
    cdio_warn ("string '%s' is getting truncated to %d characters",
              src, (unsigned int) len);

  strncpy (dst, src, len);
  if (rlen < len)
    memset(dst+rlen, ' ', len-rlen);
  return dst;
}