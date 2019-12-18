#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int zap_normflags; } ;
typedef  TYPE_1__ zap_t ;
struct TYPE_10__ {int zn_key_intlen; char const* zn_key_orig; int zn_matchtype; int zn_normflags; char const* zn_normbuf; char const* zn_key_norm; void* zn_key_norm_numints; int /*<<< orphan*/  zn_hash; void* zn_key_orig_numints; TYPE_1__* zn_zap; } ;
typedef  TYPE_2__ zap_name_t ;
typedef  int matchtype_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int MT_MATCH_CASE ; 
 int U8_TEXTPREP_TOUPPER ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 void* strlen (char const*) ; 
 int /*<<< orphan*/  zap_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_name_free (TYPE_2__*) ; 
 scalar_t__ zap_normalize (TYPE_1__*,char const*,char const*,int) ; 

zap_name_t *
zap_name_alloc(zap_t *zap, const char *key, matchtype_t mt)
{
	zap_name_t *zn = kmem_alloc(sizeof (zap_name_t), KM_SLEEP);

	zn->zn_zap = zap;
	zn->zn_key_intlen = sizeof (*key);
	zn->zn_key_orig = key;
	zn->zn_key_orig_numints = strlen(zn->zn_key_orig) + 1;
	zn->zn_matchtype = mt;
	zn->zn_normflags = zap->zap_normflags;

	/*
	 * If we're dealing with a case sensitive lookup on a mixed or
	 * insensitive fs, remove U8_TEXTPREP_TOUPPER or the lookup
	 * will fold case to all caps overriding the lookup request.
	 */
	if (mt & MT_MATCH_CASE)
		zn->zn_normflags &= ~U8_TEXTPREP_TOUPPER;

	if (zap->zap_normflags) {
		/*
		 * We *must* use zap_normflags because this normalization is
		 * what the hash is computed from.
		 */
		if (zap_normalize(zap, key, zn->zn_normbuf,
		    zap->zap_normflags) != 0) {
			zap_name_free(zn);
			return (NULL);
		}
		zn->zn_key_norm = zn->zn_normbuf;
		zn->zn_key_norm_numints = strlen(zn->zn_key_norm) + 1;
	} else {
		if (mt != 0) {
			zap_name_free(zn);
			return (NULL);
		}
		zn->zn_key_norm = zn->zn_key_orig;
		zn->zn_key_norm_numints = zn->zn_key_orig_numints;
	}

	zn->zn_hash = zap_hash(zn);

	if (zap->zap_normflags != zn->zn_normflags) {
		/*
		 * We *must* use zn_normflags because this normalization is
		 * what the matching is based on.  (Not the hash!)
		 */
		if (zap_normalize(zap, key, zn->zn_normbuf,
		    zn->zn_normflags) != 0) {
			zap_name_free(zn);
			return (NULL);
		}
		zn->zn_key_norm_numints = strlen(zn->zn_key_norm) + 1;
	}

	return (zn);
}