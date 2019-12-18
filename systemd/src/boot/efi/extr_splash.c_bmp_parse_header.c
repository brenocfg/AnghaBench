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
struct bmp_map {int dummy; } ;
struct bmp_file {char* signature; int size; int offset; } ;
struct bmp_dib {int size; int depth; int compression; int x; int y; int colors_used; } ;
typedef  int UINTN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 

EFI_STATUS bmp_parse_header(UINT8 *bmp, UINTN size, struct bmp_dib **ret_dib,
                            struct bmp_map **ret_map, UINT8 **pixmap) {
        struct bmp_file *file;
        struct bmp_dib *dib;
        struct bmp_map *map;
        UINTN row_size;

        if (size < sizeof(struct bmp_file) + sizeof(struct bmp_dib))
                return EFI_INVALID_PARAMETER;

        /* check file header */
        file = (struct bmp_file *)bmp;
        if (file->signature[0] != 'B' || file->signature[1] != 'M')
                return EFI_INVALID_PARAMETER;
        if (file->size != size)
                return EFI_INVALID_PARAMETER;
        if (file->size < file->offset)
                return EFI_INVALID_PARAMETER;

        /*  check device-independent bitmap */
        dib = (struct bmp_dib *)(bmp + sizeof(struct bmp_file));
        if (dib->size < sizeof(struct bmp_dib))
                return EFI_UNSUPPORTED;

        switch (dib->depth) {
        case 1:
        case 4:
        case 8:
        case 24:
                if (dib->compression != 0)
                        return EFI_UNSUPPORTED;

                break;

        case 16:
        case 32:
                if (dib->compression != 0 && dib->compression != 3)
                        return EFI_UNSUPPORTED;

                break;

        default:
                return EFI_UNSUPPORTED;
        }

        row_size = ((UINTN) dib->depth * dib->x + 31) / 32 * 4;
        if (file->size - file->offset <  dib->y * row_size)
                return EFI_INVALID_PARAMETER;
        if (row_size * dib->y > 64 * 1024 * 1024)
                return EFI_INVALID_PARAMETER;

        /* check color table */
        map = (struct bmp_map *)(bmp + sizeof(struct bmp_file) + dib->size);
        if (file->offset < sizeof(struct bmp_file) + dib->size)
                return EFI_INVALID_PARAMETER;

        if (file->offset > sizeof(struct bmp_file) + dib->size) {
                UINT32 map_count;
                UINTN map_size;

                if (dib->colors_used)
                        map_count = dib->colors_used;
                else {
                        switch (dib->depth) {
                        case 1:
                        case 4:
                        case 8:
                                map_count = 1 << dib->depth;
                                break;

                        default:
                                map_count = 0;
                                break;
                        }
                }

                map_size = file->offset - (sizeof(struct bmp_file) + dib->size);
                if (map_size != sizeof(struct bmp_map) * map_count)
                        return EFI_INVALID_PARAMETER;
        }

        *ret_map = map;
        *ret_dib = dib;
        *pixmap = bmp + file->offset;

        return EFI_SUCCESS;
}