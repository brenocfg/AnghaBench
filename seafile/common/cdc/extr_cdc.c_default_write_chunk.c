#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chksum_str ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  block_buf; int /*<<< orphan*/  checksum; } ;
typedef  TYPE_1__ CDCDescriptor ;

/* Variables and functions */
 int CHECKSUM_LENGTH ; 
 int NAME_MAX_SZ ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int g_open (char*,int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int writen (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int default_write_chunk (CDCDescriptor *chunk_descr)
{
    char filename[NAME_MAX_SZ];
    char chksum_str[CHECKSUM_LENGTH *2 + 1];
    int fd_chunk, ret;

    memset(chksum_str, 0, sizeof(chksum_str));
    rawdata_to_hex (chunk_descr->checksum, chksum_str, CHECKSUM_LENGTH);
    snprintf (filename, NAME_MAX_SZ, "./%s", chksum_str);
    fd_chunk = g_open (filename, O_RDWR | O_CREAT | O_BINARY, 0644);
    if (fd_chunk < 0)
        return -1;    
    
    ret = writen (fd_chunk, chunk_descr->block_buf, chunk_descr->len);
    close (fd_chunk);
    return ret;
}