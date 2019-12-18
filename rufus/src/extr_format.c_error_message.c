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
typedef  int errcode_t ;

/* Variables and functions */
 int ERROR_SEVERITY_ERROR ; 
#define  EXT2_ET_BAD_BLOCK_IN_INODE_TABLE 203 
#define  EXT2_ET_BAD_CRC 202 
#define  EXT2_ET_BAD_DESC_SIZE 201 
#define  EXT2_ET_BAD_DEVICE_NAME 200 
#define  EXT2_ET_BAD_MAGIC 199 
 int EXT2_ET_BASE ; 
#define  EXT2_ET_BLOCK_ALLOC_FAIL 198 
#define  EXT2_ET_BLOCK_BITMAP_CSUM_INVALID 197 
#define  EXT2_ET_BLOCK_BITMAP_READ 196 
#define  EXT2_ET_BLOCK_BITMAP_WRITE 195 
#define  EXT2_ET_CALLBACK_NOTHANDLED 194 
#define  EXT2_ET_CANCEL_REQUESTED 193 
#define  EXT2_ET_CORRUPT_JOURNAL_SB 192 
#define  EXT2_ET_CORRUPT_SUPERBLOCK 191 
#define  EXT2_ET_DIR_CORRUPTED 190 
#define  EXT2_ET_DIR_CSUM_INVALID 189 
#define  EXT2_ET_DIR_EXISTS 188 
#define  EXT2_ET_DIR_NO_SPACE 187 
#define  EXT2_ET_EA_INODE_CORRUPTED 186 
#define  EXT2_ET_EXTENT_CSUM_INVALID 185 
#define  EXT2_ET_EXT_ATTR_CSUM_INVALID 184 
#define  EXT2_ET_FILESYSTEM_CORRUPTED 183 
#define  EXT2_ET_FILE_EXISTS 182 
#define  EXT2_ET_FILE_NOT_FOUND 181 
#define  EXT2_ET_FILE_RO 180 
#define  EXT2_ET_FILE_TOO_BIG 179 
#define  EXT2_ET_GDESC_BAD_BLOCK_MAP 178 
#define  EXT2_ET_GDESC_BAD_INODE_MAP 177 
#define  EXT2_ET_GDESC_BAD_INODE_TABLE 176 
#define  EXT2_ET_GDESC_READ 175 
#define  EXT2_ET_GDESC_WRITE 174 
#define  EXT2_ET_INODE_ALLOC_FAIL 173 
#define  EXT2_ET_INODE_BITMAP_CSUM_INVALID 172 
#define  EXT2_ET_INODE_BITMAP_READ 171 
#define  EXT2_ET_INODE_BITMAP_WRITE 170 
#define  EXT2_ET_INODE_CORRUPTED 169 
#define  EXT2_ET_INODE_CSUM_INVALID 168 
#define  EXT2_ET_INODE_IS_GARBAGE 167 
#define  EXT2_ET_INODE_TABLE_READ 166 
#define  EXT2_ET_INODE_TABLE_WRITE 165 
#define  EXT2_ET_INVALID_ARGUMENT 164 
#define  EXT2_ET_IO_CHANNEL_NO_SUPPORT_64 163 
#define  EXT2_ET_JOURNAL_FLAGS_WRONG 162 
#define  EXT2_ET_JOURNAL_NOT_BLOCK 161 
#define  EXT2_ET_JOURNAL_TOO_SMALL 160 
#define  EXT2_ET_LLSEEK_FAILED 159 
#define  EXT2_ET_MAGIC_BADBLOCKS_ITERATE 158 
#define  EXT2_ET_MAGIC_BADBLOCKS_LIST 157 
#define  EXT2_ET_MAGIC_BLOCK_BITMAP 156 
#define  EXT2_ET_MAGIC_EXT2FS_FILSYS 155 
#define  EXT2_ET_MAGIC_EXTENT_HANDLE 154 
#define  EXT2_ET_MAGIC_GENERIC_BITMAP 153 
#define  EXT2_ET_MAGIC_ICOUNT 152 
#define  EXT2_ET_MAGIC_INODE_BITMAP 151 
#define  EXT2_ET_MAGIC_INODE_SCAN 150 
#define  EXT2_ET_MAGIC_IO_CHANNEL 149 
#define  EXT2_ET_MAGIC_IO_MANAGER 148 
#define  EXT2_ET_MISSING_INODE_TABLE 147 
#define  EXT2_ET_MMP_CSUM_INVALID 146 
#define  EXT2_ET_NEXT_INODE_READ 145 
#define  EXT2_ET_NO_CURRENT_NODE 144 
#define  EXT2_ET_NO_DIRECTORY 143 
#define  EXT2_ET_NO_JOURNAL 142 
#define  EXT2_ET_NO_JOURNAL_SB 141 
#define  EXT2_ET_NO_MEMORY 140 
#define  EXT2_ET_OP_NOT_SUPPORTED 139 
#define  EXT2_ET_RO_FILSYS 138 
#define  EXT2_ET_RO_UNSUPP_FEATURE 137 
#define  EXT2_ET_SB_CSUM_INVALID 136 
#define  EXT2_ET_SHORT_READ 135 
#define  EXT2_ET_SHORT_WRITE 134 
#define  EXT2_ET_TOOSMALL 133 
#define  EXT2_ET_TOO_MANY_INODES 132 
#define  EXT2_ET_UNEXPECTED_BLOCK_SIZE 131 
#define  EXT2_ET_UNIMPLEMENTED 130 
#define  EXT2_ET_UNKNOWN_CSUM 129 
#define  EXT2_ET_UNSUPP_FEATURE 128 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int FormatStatus ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,...) ; 

const char* error_message(errcode_t error_code)
{
	static char error_string[256];

	switch (error_code) {
	case EXT2_ET_MAGIC_EXT2FS_FILSYS:
	case EXT2_ET_MAGIC_BADBLOCKS_LIST:
	case EXT2_ET_MAGIC_BADBLOCKS_ITERATE:
	case EXT2_ET_MAGIC_INODE_SCAN:
	case EXT2_ET_MAGIC_IO_CHANNEL:
	case EXT2_ET_MAGIC_IO_MANAGER:
	case EXT2_ET_MAGIC_BLOCK_BITMAP:
	case EXT2_ET_MAGIC_INODE_BITMAP:
	case EXT2_ET_MAGIC_GENERIC_BITMAP:
	case EXT2_ET_MAGIC_ICOUNT:
	case EXT2_ET_MAGIC_EXTENT_HANDLE:
	case EXT2_ET_BAD_MAGIC:
		return "Bad magic";
	case EXT2_ET_RO_FILSYS:
		return "Read-only file system";
	case EXT2_ET_GDESC_BAD_BLOCK_MAP:
	case EXT2_ET_GDESC_BAD_INODE_MAP:
	case EXT2_ET_GDESC_BAD_INODE_TABLE:
		return "Bad map or table";
	case EXT2_ET_UNEXPECTED_BLOCK_SIZE:
		return "Unexpected block size";
	case EXT2_ET_DIR_CORRUPTED:
		return "Corrupted entry";
	case EXT2_ET_GDESC_READ:
	case EXT2_ET_GDESC_WRITE:
	case EXT2_ET_INODE_BITMAP_WRITE:
	case EXT2_ET_INODE_BITMAP_READ:
	case EXT2_ET_BLOCK_BITMAP_WRITE:
	case EXT2_ET_BLOCK_BITMAP_READ:
	case EXT2_ET_INODE_TABLE_WRITE:
	case EXT2_ET_INODE_TABLE_READ:
	case EXT2_ET_NEXT_INODE_READ:
	case EXT2_ET_SHORT_READ:
	case EXT2_ET_SHORT_WRITE:
		return "read/write error";
	case EXT2_ET_DIR_NO_SPACE:
		return "no space left";
	case EXT2_ET_TOOSMALL:
		return "Too small";
	case EXT2_ET_BAD_DEVICE_NAME:
		return "Bad device name";
	case EXT2_ET_MISSING_INODE_TABLE:
		return "Missing inode table";
	case EXT2_ET_CORRUPT_SUPERBLOCK:
		return "Superblock is corrupted";
	case EXT2_ET_CALLBACK_NOTHANDLED:
		return "Unhandled callback";
	case EXT2_ET_BAD_BLOCK_IN_INODE_TABLE:
		return "Bad block in inode table";
	case EXT2_ET_UNSUPP_FEATURE:
	case EXT2_ET_RO_UNSUPP_FEATURE:
	case EXT2_ET_UNIMPLEMENTED:
		return "Unsupported feature";
	case EXT2_ET_LLSEEK_FAILED:
		return "Seek failed";
	case EXT2_ET_NO_MEMORY:
	case EXT2_ET_BLOCK_ALLOC_FAIL:
	case EXT2_ET_INODE_ALLOC_FAIL:
		return "Out of memory";
	case EXT2_ET_INVALID_ARGUMENT:
		return "Invalid argument";
	case EXT2_ET_NO_DIRECTORY:
		return "No directory";
	case EXT2_ET_FILE_NOT_FOUND:
		return "File not found";
	case EXT2_ET_FILE_RO:
		return "File is read-only";
	case EXT2_ET_DIR_EXISTS:
		return "Directory already exists";
	case EXT2_ET_CANCEL_REQUESTED:
		return "Cancel requested";
	case EXT2_ET_FILE_TOO_BIG:
		return "File too big";
	case EXT2_ET_JOURNAL_NOT_BLOCK:
	case EXT2_ET_NO_JOURNAL_SB:
		return "No journal superblock";
	case EXT2_ET_JOURNAL_TOO_SMALL:
		return "Journal too small";
	case EXT2_ET_NO_JOURNAL:
		return "No journal";
	case EXT2_ET_TOO_MANY_INODES:
		return "Too many inodes";
	case EXT2_ET_NO_CURRENT_NODE:
		return "No current node";
	case EXT2_ET_OP_NOT_SUPPORTED:
		return "Operation not supported";
	case EXT2_ET_IO_CHANNEL_NO_SUPPORT_64:
		return "I/O Channel does not support 64-bit operation";
	case EXT2_ET_BAD_DESC_SIZE:
		return "Bad descriptor size";
	case EXT2_ET_INODE_CSUM_INVALID:
	case EXT2_ET_INODE_BITMAP_CSUM_INVALID:
	case EXT2_ET_EXTENT_CSUM_INVALID:
	case EXT2_ET_DIR_CSUM_INVALID:
	case EXT2_ET_EXT_ATTR_CSUM_INVALID:
	case EXT2_ET_SB_CSUM_INVALID:
	case EXT2_ET_BLOCK_BITMAP_CSUM_INVALID:
	case EXT2_ET_MMP_CSUM_INVALID:
		return "Invalid checksum";
	case EXT2_ET_UNKNOWN_CSUM:
		return "Unknown checksum";
	case EXT2_ET_FILE_EXISTS:
		return "File exists";
	case EXT2_ET_INODE_IS_GARBAGE:
		return "Inode is garbage";
	case EXT2_ET_JOURNAL_FLAGS_WRONG:
		return "Wrong journal flags";
	case EXT2_ET_FILESYSTEM_CORRUPTED:
		return "File system is corrupted";
	case EXT2_ET_BAD_CRC:
		return "Bad CRC";
	case EXT2_ET_CORRUPT_JOURNAL_SB:
		return "Journal Superblock is corrupted";
	case EXT2_ET_INODE_CORRUPTED:
	case EXT2_ET_EA_INODE_CORRUPTED:
		return "Inode is corrupted";
	default:
		if ((error_code > EXT2_ET_BASE) && error_code < (EXT2_ET_BASE + 1000)) {
			static_sprintf(error_string, "Unknown ext2fs error %ld (EXT2_ET_BASE + %ld)", error_code, error_code - EXT2_ET_BASE);
		} else {
			SetLastError((FormatStatus == 0) ? (ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | (error_code & 0xFFFF)) : FormatStatus);
			static_sprintf(error_string, WindowsErrorString());
		}
		return error_string;
	}
}