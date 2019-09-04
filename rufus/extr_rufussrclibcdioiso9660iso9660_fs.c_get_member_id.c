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
typedef  int /*<<< orphan*/  iso9660_t ;
typedef  char cdio_utf8_t ;

/* Variables and functions */
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  cdio_warn (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static inline bool
get_member_id(iso9660_t *p_iso, cdio_utf8_t **p_psz_member_id,
              char* pvd_member, char* svd_member, size_t max_size)
{
  int j;
  bool strip;

  if (!p_iso) {
    *p_psz_member_id = NULL;
    return false;
  }
#ifdef HAVE_JOLIET
  if (p_iso->u_joliet_level) {
    /* Translate USC-2 string from Secondary Volume Descriptor */
    if (cdio_charset_to_utf8(svd_member, max_size,
                            p_psz_member_id, "UCS-2BE")) {
      /* NB: *p_psz_member_id is never NULL on success. */
      if (strncmp(*p_psz_member_id, pvd_member,
                  strlen(*p_psz_member_id)) != 0) {
        /* Strip trailing spaces */
        for (j = strlen(*p_psz_member_id)-1; j >= 0; j--) {
          if ((*p_psz_member_id)[j] != ' ')
            break;
          (*p_psz_member_id)[j] = '\0';
        }
        if ((*p_psz_member_id)[0] != 0) {
          /* Joliet string is not empty and differs from
             non Joliet one => use it */
          return true;
        }
      }
      /* Joliet string was either empty or same */
      free(*p_psz_member_id);
    }
  }
#endif /*HAVE_JOLIET*/
  *p_psz_member_id = calloc(max_size+1, sizeof(cdio_utf8_t));
  if (!*p_psz_member_id) {
    cdio_warn("Memory allocation error");
    return false;
  }
  /* Copy string while removing trailing spaces */
  (*p_psz_member_id)[max_size] = 0;
  for (strip=true, j=max_size-1; j>=0; j--) {
    if (strip && (pvd_member[j] == ' '))
      continue;
    strip = false;
    (*p_psz_member_id)[j] = pvd_member[j];
  }
  if (strlen(*p_psz_member_id) == 0) {
    free(*p_psz_member_id);
    *p_psz_member_id = NULL;
    return false;
  }
  return true;
}