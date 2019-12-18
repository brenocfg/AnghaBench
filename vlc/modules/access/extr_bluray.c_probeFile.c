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
typedef  scalar_t__ uint8_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  peek ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int decode_descriptor_tag (scalar_t__*) ; 
 int fstat (int,struct stat*) ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int read (int,scalar_t__*,int) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char const*,int) ; 

__attribute__((used)) static int probeFile(const char *psz_name)
{
    struct stat stat_info;
    uint8_t peek[2048];
    unsigned i;
    int ret = VLC_EGENERIC;
    int fd;

    fd = vlc_open(psz_name, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        return VLC_EGENERIC;
    }

    if (fstat(fd, &stat_info) == -1) {
        goto bailout;
    }
    if (!S_ISREG(stat_info.st_mode) && !S_ISBLK(stat_info.st_mode)) {
        goto bailout;
    }

    /* first sector should be filled with zeros */
    if (read(fd, peek, sizeof(peek)) != sizeof(peek)) {
        goto bailout;
    }
    for (i = 0; i < sizeof(peek); i++) {
        if (peek[ i ]) {
            goto bailout;
        }
    }

    /* Check AVDP tag checksum */
    if (lseek(fd, 256 * 2048, SEEK_SET) == -1 ||
        read(fd, peek, 16) != 16 ||
        decode_descriptor_tag(peek) != 2) {
        goto bailout;
    }

    ret = VLC_SUCCESS;

bailout:
    vlc_close(fd);
    return ret;
}