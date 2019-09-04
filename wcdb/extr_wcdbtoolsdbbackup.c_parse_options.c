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
 int /*<<< orphan*/  DBBAK_OP_BACKUP ; 
 int /*<<< orphan*/  DBBAK_OP_RECOVER ; 
 int /*<<< orphan*/  MMBAK_FLAG_FIX_CORRUPTION ; 
 int /*<<< orphan*/  MMBAK_FLAG_INCREMENTAL ; 
 int /*<<< orphan*/  MMBAK_FLAG_NO_CIPHER ; 
 int /*<<< orphan*/  MMBAK_FLAG_NO_COMPRESS ; 
 int /*<<< orphan*/  MMBAK_FLAG_NO_CREATE_TABLE ; 
 int /*<<< orphan*/  MMBAK_LOG_ERROR ; 
 int atoi (void*) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* g_db_path ; 
 void* g_dbkey ; 
 void* g_dump_path ; 
 int /*<<< orphan*/  g_flags ; 
 int /*<<< orphan*/ * g_key ; 
 int /*<<< orphan*/  g_operation ; 
 int /*<<< orphan*/  g_options ; 
 void* g_tabdesc_path ; 
 int g_verbose ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  print_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlcipher_set_default_kdf_iter (int) ; 
 int /*<<< orphan*/  sqlcipher_set_default_pagesize (int) ; 
 int /*<<< orphan*/  sqlcipher_set_default_use_hmac (int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

__attribute__((used)) static void parse_options(int argc, char *argv[])
{
	int opt;
	int value;
	
	// parse operation
	if (argc < 2) usage(argv[0]);
	
	const char *opstr = argv[1];
	if (!strcmp(opstr, "backup"))
		g_operation = DBBAK_OP_BACKUP;
	else if (!strcmp(opstr, "recover"))
		g_operation = DBBAK_OP_RECOVER;
	else usage(argv[0]);

	// default to SQLCipher version 1, thanks to kkdb.
	sqlcipher_set_default_kdf_iter(4000);
	sqlcipher_set_default_use_hmac(0);
	
	// parse options
	optind = 2;
	while ((opt = getopt_long(argc, argv, "vzZfFtTio:d:K:k:", g_options, NULL)) != -1)
	{
		switch (opt)
		{
		case 'v':	// verbose
			g_verbose = 1;
			break;
		case 'z':	// compress
			g_flags &= (~MMBAK_FLAG_NO_COMPRESS);
			break;
		case 'Z':	// no-compress
			g_flags |= MMBAK_FLAG_NO_COMPRESS;
			break;
		case 'f':	// fix
			g_flags |= MMBAK_FLAG_FIX_CORRUPTION;
			break;
		case 'F':	// no-fix
			g_flags &= (~MMBAK_FLAG_FIX_CORRUPTION);
			break;
		case 't':	// create-table
			g_flags &= (~MMBAK_FLAG_NO_CREATE_TABLE);
			break;
		case 'T':	// no-create-table
			g_flags |= MMBAK_FLAG_NO_CREATE_TABLE;
			break;
		case 'i':	// incremental
			g_flags |= MMBAK_FLAG_INCREMENTAL;
			break;
		case 'o':	// output
			g_dump_path = optarg;
			break;
		case 'd':	// tabdesc
			g_tabdesc_path = optarg;
			break;
		case 'K':	// dbkey
			g_dbkey = optarg;
			break;
		case 'k':	// key
			g_key = optarg;
			break;
		case 0x100:	// version
			value = atoi(optarg);
			if (value == 1)
			{
				sqlcipher_set_default_kdf_iter(4000);
				sqlcipher_set_default_use_hmac(0);
			}
			else if (value == 2)
			{
				sqlcipher_set_default_kdf_iter(4000);
				sqlcipher_set_default_use_hmac(1);
			}
			else if (value == 3)
			{
				sqlcipher_set_default_kdf_iter(64000);
				sqlcipher_set_default_use_hmac(1);
			}
			else
			{
				print_log(MMBAK_LOG_ERROR, "Version must be 1, 2 or 3");
				exit(-1);
			}
			break;
		case 0x101:	// page-size
			value = atoi(optarg);
			if (value != 512 && value != 1024 && value != 2048 && value != 4096 &&
					value != 8192 && value != 16384 && value != 32768 && value != 65536)
			{
				print_log(MMBAK_LOG_ERROR, "Page size must be 512, 1024, 2048, ..., 65536");
				exit(-1);
			}
			sqlcipher_set_default_pagesize(value);
			break;
		default:	// ?
			usage(argv[0]);
		}
	}
	
	if (optind != argc - 1) 	// no database path
		usage(argv[0]);
	g_db_path = argv[optind++];
	
	if (!g_dump_path)
	{
		print_log(MMBAK_LOG_ERROR, "Output path must be specified.");
		usage(argv[0]);
	}
	
	if (g_key == NULL)
		g_flags |= MMBAK_FLAG_NO_CIPHER;
}