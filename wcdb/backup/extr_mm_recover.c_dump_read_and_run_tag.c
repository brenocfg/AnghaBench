#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_6__ {int /*<<< orphan*/  total_out; int /*<<< orphan*/  total_in; } ;
struct TYPE_7__ {int succ_count; TYPE_1__ zstrm; int /*<<< orphan*/  db; int /*<<< orphan*/  fail_count; scalar_t__ canceled; } ;
typedef  TYPE_2__ mm_recover_ctx ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  databuf ;

/* Variables and functions */
 int /*<<< orphan*/  CUSTOM_FAIL (int,char*) ; 
 int /*<<< orphan*/  LOGE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_AND_FAIL (char*,int) ; 
 int /*<<< orphan*/  MEMORY_ALLOC_FAIL (int,int) ; 
 int MMBAK_RET_CANCELED ; 
 int MMBAK_RET_FAILED ; 
 int MMBAK_RET_OK ; 
#define  MMBAK_TAG_BIND_BLOB 140 
#define  MMBAK_TAG_BIND_BLOB_SHORT 139 
#define  MMBAK_TAG_BIND_FLOAT 138 
#define  MMBAK_TAG_BIND_NULL 137 
#define  MMBAK_TAG_BIND_TEXT 136 
#define  MMBAK_TAG_BIND_TEXT_SHORT 135 
#define  MMBAK_TAG_BIND_VARINT 134 
#define  MMBAK_TAG_BIND_VARINT_MINUS 133 
#define  MMBAK_TAG_END_ROW 132 
#define  MMBAK_TAG_END_SQL 131 
#define  MMBAK_TAG_LARGE_DATA 130 
#define  MMBAK_TAG_SQL_ONESHOT 129 
#define  MMBAK_TAG_SQL_REPEATED 128 
 int /*<<< orphan*/  READ_STREAM_FAIL (int,int,int) ; 
 int /*<<< orphan*/  SQLITE_FAIL_ERRMSG_WARN (int,char*,char*) ; 
 int /*<<< orphan*/  SQLITE_FAIL_GETMSG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQLITE_FAIL_GETMSG_WARN (int,char*,int /*<<< orphan*/ ) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_ROW ; 
 int dump_read_stream (TYPE_2__*,...) ; 
 int /*<<< orphan*/  dump_read_varint (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  sqlite3_bind_double (int /*<<< orphan*/ *,int,double) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,char*,int /*<<< orphan*/  (*) (char*)) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 char* sqlite3_sql (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_read_and_run_tag(mm_recover_ctx *ctx, int fatal)
{
    int ret;
    uint8_t tag;
    uint8_t length_short;
    uint16_t length;
    char *data = NULL;
    char *p_data = NULL;
    sqlite3_stmt *stmt = NULL;
    int bind_idx;
    char *errmsg = NULL;
    char databuf[8192];

    while (!ctx->canceled) {
        ret = dump_read_stream(ctx, &tag, 1);
        if (ret == 0)
            return MMBAK_RET_OK;
        else if (ret != 1)
            return MMBAK_RET_FAILED;

        switch (tag) {
            case MMBAK_TAG_LARGE_DATA:
                if (data != NULL)
                    CUSTOM_FAIL(tag, "Internal error.");
                if ((ret = dump_read_stream(ctx, &length, 2)) != 2)
                    READ_STREAM_FAIL(tag, 2, ret);

                data = (char *) malloc((length + 1) * 65536);
                if (!data)
                    MEMORY_ALLOC_FAIL(tag, (length + 1) * 65536);

                if ((ret = dump_read_stream(ctx, data, length * 65536)) !=
                    length * 65536)
                    READ_STREAM_FAIL(tag, length * 65536, ret);

                p_data = data;
                //LOGD("[%s] len=%u * 65536", "LARGE_DATA", length);
                break;

            case MMBAK_TAG_SQL_ONESHOT:
                if ((ret = dump_read_stream(ctx, &length, 2)) != 2)
                    READ_STREAM_FAIL(tag, 2, ret);

                if (!p_data) {
                    if (length < sizeof(databuf))
                        data = databuf;
                    else {
                        data = (char *) malloc(length + 1);
                        if (!data)
                            MEMORY_ALLOC_FAIL(tag, length + 1);
                    }
                    p_data = data;
                }

                if ((ret = dump_read_stream(ctx, p_data, length)) != length)
                    READ_STREAM_FAIL(tag, length, ret);
                p_data[length] = '\0';

                ret = sqlite3_exec(ctx->db, data, 0, 0, &errmsg);
                if (ret != SQLITE_OK) {
                    SQLITE_FAIL_ERRMSG_WARN(tag, data, errmsg);
                    if (fatal)
                        goto bail;

                    sqlite3_free(errmsg);
                    ctx->fail_count++;
                } else
                    ctx->succ_count++;

                //LOGD("[%s] sql=%s", "SQL_ONESHOT", data);
                if (data != databuf)
                    free(data);
                p_data = data = NULL;
                break;

            case MMBAK_TAG_SQL_REPEATED:
                if ((ret = dump_read_stream(ctx, &length, 2)) != 2)
                    READ_STREAM_FAIL(tag, 2, ret);

                if (!p_data) {
                    if (length < sizeof(databuf))
                        data = databuf;
                    else {
                        data = (char *) malloc(length + 1);
                        if (!data)
                            MEMORY_ALLOC_FAIL(tag, length + 1);
                    }
                    p_data = data;
                }
                if ((ret = dump_read_stream(ctx, p_data, length)) != length)
                    READ_STREAM_FAIL(tag, length, ret);
                p_data[length] = '\0';

                ret = sqlite3_prepare_v2(ctx->db, data,
                                         (p_data - data) + length, &stmt, NULL);
                if (ret != SQLITE_OK) {
                    SQLITE_FAIL_GETMSG_WARN(tag, data, ctx->db);
                    if (fatal)
                        goto bail;

                    stmt = NULL;
                }

                //LOGD("[%s] sql=%s", "SQL_REPEATED", data);
                if (data != databuf)
                    free(data);
                p_data = data = NULL;

                bind_idx = 0;
                do {
                    // check exit status.
                    if (ctx->canceled) {
                        if (data && data != databuf)
                            free(data);
                        if (stmt)
                            sqlite3_finalize(stmt);
                        return MMBAK_RET_CANCELED;
                    }

                    if ((ret = dump_read_stream(ctx, &tag, 1)) != 1)
                        READ_STREAM_FAIL(tag, 1, ret);

                    switch (tag) {
                        union {
                            int64_t i;
                            double f;
                        } value;

                        case MMBAK_TAG_LARGE_DATA:
                            if (data != NULL)
                                CUSTOM_FAIL(tag, "Internal error.");
                            if ((ret = dump_read_stream(ctx, &length, 2)) != 2)
                                READ_STREAM_FAIL(tag, 2, ret);

                            data = (char *) malloc((length + 1) * 65536);
                            if (!data)
                                MEMORY_ALLOC_FAIL(tag, (length + 1) * 65536);

                            if ((ret = dump_read_stream(ctx, data,
                                                        length * 65536)) !=
                                length * 65536)
                                READ_STREAM_FAIL(tag, length * 65536, ret);

                            p_data = data;
                            //LOGD(" > [%s] len=%u * 65536", "LARGE_DATA", length);
                            break;

                        case MMBAK_TAG_END_ROW:
                            if (!stmt)
                                ctx->fail_count++;
                            else {
                                while (sqlite3_step(stmt) == SQLITE_ROW) {
                                }
                                ret = sqlite3_reset(stmt);
                                if (ret != SQLITE_OK) {
                                    SQLITE_FAIL_GETMSG_WARN(
                                        tag, sqlite3_sql(stmt), ctx->db);
                                    if (fatal)
                                        goto bail;

                                    ctx->fail_count++;
                                } else {
                                    ctx->succ_count++;
                                    if (ctx->succ_count % 256 == 0) {
                                        // We have run 256 insertions, do a transaction commit.
                                        ret = sqlite3_exec(ctx->db,
                                                           "COMMIT; BEGIN;", 0,
                                                           0, &errmsg);
                                        if (ret != SQLITE_OK) {
                                            SQLITE_FAIL_ERRMSG_WARN(tag, data,
                                                                    errmsg);
                                            if (fatal)
                                                goto bail;

                                            sqlite3_free(errmsg);
                                            ctx->fail_count++;
                                        }
                                    }
                                }
                            }

                            bind_idx = 0;
                            //LOGD(" > [%s]", "END_ROW");
                            break;

                        case MMBAK_TAG_END_SQL:
                            //LOGD(" > [%s]", "END_SQL");
                            break; // end of loop

                        case MMBAK_TAG_BIND_NULL:
                            if (stmt)
                                sqlite3_bind_null(stmt, ++bind_idx);
                            //LOGD(" > [%s]", "BIND_NULL");
                            break;

                        case MMBAK_TAG_BIND_VARINT:
                        case MMBAK_TAG_BIND_VARINT_MINUS:
                            if (dump_read_varint(
                                    ctx, &value.i,
                                    tag == MMBAK_TAG_BIND_VARINT_MINUS) != 0)
                                CUSTOM_FAIL(tag, "Read varint failed.");
                            if (stmt)
                                sqlite3_bind_int64(stmt, ++bind_idx, value.i);
                            //LOGD(" > [%s] value=%lld", tag2text(tag), value.i);
                            break;

                        case MMBAK_TAG_BIND_FLOAT:
                            if ((ret = dump_read_stream(ctx, &value, 8)) != 8)
                                READ_STREAM_FAIL(tag, 8, ret);
                            if (stmt)
                                sqlite3_bind_double(stmt, ++bind_idx, value.f);
                            //LOGD(" > [%s] value=%f", "BIND_FLOAT", value.f);
                            break;

                        case MMBAK_TAG_BIND_TEXT:
                        case MMBAK_TAG_BIND_BLOB:
                            if ((ret = dump_read_stream(ctx, &length, 2)) != 2)
                                READ_STREAM_FAIL(tag, 2, ret);
                            if (!p_data) {
                                data = (char *) malloc(length);
                                if (!data)
                                    MEMORY_ALLOC_FAIL(tag, length);
                                p_data = data;
                            }
                            if ((ret = dump_read_stream(ctx, p_data, length)) !=
                                length)
                                READ_STREAM_FAIL(tag, length, ret);

                            //LOGD(" > [%s] value=%s", tag2text(tag), tag == MMBAK_TAG_BIND_TEXT ? data : "(BLOB)");
                            if (stmt) {
                                if (tag == MMBAK_TAG_BIND_TEXT)
                                    sqlite3_bind_text(stmt, ++bind_idx, data,
                                                      (p_data - data) + length,
                                                      free);
                                else
                                    sqlite3_bind_blob(stmt, ++bind_idx, data,
                                                      (p_data - data) + length,
                                                      free);
                            } else
                                free(data);

                            p_data = data = NULL;
                            break;

                        case MMBAK_TAG_BIND_TEXT_SHORT:
                        case MMBAK_TAG_BIND_BLOB_SHORT:
                            if ((ret = dump_read_stream(ctx, &length_short,
                                                        1)) != 1)
                                READ_STREAM_FAIL(tag, 1, ret);
                            length = length_short;
                            if (!p_data) {
                                data = (char *) malloc(length);
                                if (!data)
                                    MEMORY_ALLOC_FAIL(tag, length);
                                p_data = data;
                            }
                            if ((ret = dump_read_stream(ctx, p_data, length)) !=
                                length)
                                READ_STREAM_FAIL(tag, length, ret);

                            //LOGD(" > [%s] value=%s", tag2text(tag), tag == MMBAK_TAG_BIND_TEXT_SHORT ? data : "(BLOB)");
                            if (stmt) {
                                if (tag == MMBAK_TAG_BIND_TEXT_SHORT)
                                    sqlite3_bind_text(stmt, ++bind_idx, data,
                                                      (p_data - data) + length,
                                                      free);
                                else
                                    sqlite3_bind_blob(stmt, ++bind_idx, data,
                                                      (p_data - data) + length,
                                                      free);
                            } else
                                free(data);

                            p_data = data = NULL;
                            break;

                        default:
                            LOG_AND_FAIL("Unrecognized tag: %d", tag);
                    }
                } while (tag != MMBAK_TAG_END_SQL);

                if (stmt && sqlite3_finalize(stmt) != SQLITE_OK)
                    SQLITE_FAIL_GETMSG(tag, "(FINALIZE)", ctx->db);
                break;

            default:
                LOG_AND_FAIL("Unrecognized tag: %d", tag);
        }
    }
    return MMBAK_RET_CANCELED;

bail:
    if (data && data != databuf)
        free(data);
    if (errmsg)
        sqlite3_free(errmsg);
    if (stmt)
        sqlite3_finalize(stmt);
    LOGE("Fatal Offset [in: %lu, out: %lu]", ctx->zstrm.total_in,
         ctx->zstrm.total_out);
    return MMBAK_RET_FAILED;
}