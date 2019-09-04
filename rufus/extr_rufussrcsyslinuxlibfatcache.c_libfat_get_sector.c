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
struct libfat_sector {scalar_t__ n; void* data; struct libfat_sector* next; } ;
struct libfat_filesystem {scalar_t__ (* read ) (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ;struct libfat_sector* sectors; int /*<<< orphan*/  readptr; } ;
typedef  scalar_t__ libfat_sector_t ;

/* Variables and functions */
 scalar_t__ LIBFAT_SECTOR_SIZE ; 
 int /*<<< orphan*/  _mm_free (struct libfat_sector*) ; 
 struct libfat_sector* _mm_malloc (scalar_t__,int) ; 
 int /*<<< orphan*/  libfat_flush (struct libfat_filesystem*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ; 

void *libfat_get_sector(struct libfat_filesystem *fs, libfat_sector_t n)
{
    struct libfat_sector *ls;

    for (ls = fs->sectors; ls; ls = ls->next) {
	if (ls->n == n)
	    return ls->data;	/* Found in cache */
    }

    /* Not found in cache */
    ls = _mm_malloc(sizeof(struct libfat_sector) + LIBFAT_SECTOR_SIZE, 16);
    if (!ls) {
	libfat_flush(fs);
	ls = _mm_malloc(sizeof(struct libfat_sector) + LIBFAT_SECTOR_SIZE, 16);

	if (!ls)
	    return NULL;	/* Can't allocate memory */
    }

    if (fs->read(fs->readptr, ls->data, LIBFAT_SECTOR_SIZE, n)
	!= LIBFAT_SECTOR_SIZE) {
	_mm_free(ls);
	return NULL;		/* I/O error */
    }

    ls->n = n;
    ls->next = fs->sectors;
    fs->sectors = ls;

    return ls->data;
}