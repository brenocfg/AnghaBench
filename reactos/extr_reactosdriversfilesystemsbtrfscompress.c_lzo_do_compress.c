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
typedef  int ptrdiff_t ;
typedef  scalar_t__ UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int DINDEX (int,scalar_t__ const*) ; 
 int /*<<< orphan*/  DVAL_FIRST (int,scalar_t__ const*) ; 
 int /*<<< orphan*/  DVAL_NEXT (int,scalar_t__ const*) ; 
 scalar_t__ LZO_BYTE (int) ; 
 int /*<<< orphan*/  LZO_CHECK_MPOS_NON_DET (scalar_t__ const*,int,scalar_t__ const*,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int M2_MAX_OFFSET ; 
 int M3_MARKER ; 
 int M3_MAX_OFFSET ; 
 int M4_MARKER ; 
 int /*<<< orphan*/  M4_MAX_OFFSET ; 
 int /*<<< orphan*/  STATUS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UPDATE_D (scalar_t__ const**,int /*<<< orphan*/ ,int,scalar_t__ const*) ; 
 int /*<<< orphan*/  UPDATE_I (scalar_t__ const**,int /*<<< orphan*/ ,int,scalar_t__ const*) ; 
 int /*<<< orphan*/  cycle ; 

__attribute__((used)) static NTSTATUS lzo_do_compress(const UINT8* in, UINT32 in_len, UINT8* out, UINT32* out_len, void* wrkmem) {
    const UINT8* ip;
    UINT32 dv;
    UINT8* op;
    const UINT8* in_end = in + in_len;
    const UINT8* ip_end = in + in_len - 9 - 4;
    const UINT8* ii;
    const UINT8** dict = (const UINT8**)wrkmem;

    op = out;
    ip = in;
    ii = ip;

    DVAL_FIRST(dv, ip); UPDATE_D(dict, cycle, dv, ip); ip++;
    DVAL_NEXT(dv, ip);  UPDATE_D(dict, cycle, dv, ip); ip++;
    DVAL_NEXT(dv, ip);  UPDATE_D(dict, cycle, dv, ip); ip++;
    DVAL_NEXT(dv, ip);  UPDATE_D(dict, cycle, dv, ip); ip++;

    while (1) {
        const UINT8* m_pos;
        UINT32 m_len;
        ptrdiff_t m_off;
        UINT32 lit, dindex;

        dindex = DINDEX(dv, ip);
        m_pos = dict[dindex];
        UPDATE_I(dict, cycle, dindex, ip);

        if (!LZO_CHECK_MPOS_NON_DET(m_pos, m_off, in, ip, M4_MAX_OFFSET) && m_pos[0] == ip[0] && m_pos[1] == ip[1] && m_pos[2] == ip[2]) {
            lit = (UINT32)(ip - ii);
            m_pos += 3;
            if (m_off <= M2_MAX_OFFSET)
                goto match;

            if (lit == 3) { /* better compression, but slower */
                if (op - 2 <= out)
                    return STATUS_INTERNAL_ERROR;

                op[-2] |= LZO_BYTE(3);
                *op++ = *ii++; *op++ = *ii++; *op++ = *ii++;
                goto code_match;
            }

            if (*m_pos == ip[3])
                goto match;
        }

        /* a literal */
        ++ip;
        if (ip >= ip_end)
            break;
        DVAL_NEXT(dv, ip);
        continue;

        /* a match */
match:
        /* store current literal run */
        if (lit > 0) {
            UINT32 t = lit;

            if (t <= 3) {
                if (op - 2 <= out)
                    return STATUS_INTERNAL_ERROR;

                op[-2] |= LZO_BYTE(t);
            } else if (t <= 18)
                *op++ = LZO_BYTE(t - 3);
            else {
                UINT32 tt = t - 18;

                *op++ = 0;
                while (tt > 255) {
                    tt -= 255;
                    *op++ = 0;
                }

                if (tt <= 0)
                    return STATUS_INTERNAL_ERROR;

                *op++ = LZO_BYTE(tt);
            }

            do {
                *op++ = *ii++;
            } while (--t > 0);
        }


        /* code the match */
code_match:
        if (ii != ip)
            return STATUS_INTERNAL_ERROR;

        ip += 3;
        if (*m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++ ||
            *m_pos++ != *ip++ || *m_pos++ != *ip++ || *m_pos++ != *ip++) {
            --ip;
            m_len = (UINT32)(ip - ii);

            if (m_len < 3 || m_len > 8)
                return STATUS_INTERNAL_ERROR;

            if (m_off <= M2_MAX_OFFSET) {
                m_off -= 1;
                *op++ = LZO_BYTE(((m_len - 1) << 5) | ((m_off & 7) << 2));
                *op++ = LZO_BYTE(m_off >> 3);
            } else if (m_off <= M3_MAX_OFFSET) {
                m_off -= 1;
                *op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
                goto m3_m4_offset;
            } else {
                m_off -= 0x4000;

                if (m_off <= 0 || m_off > 0x7fff)
                    return STATUS_INTERNAL_ERROR;

                *op++ = LZO_BYTE(M4_MARKER | ((m_off & 0x4000) >> 11) | (m_len - 2));
                goto m3_m4_offset;
            }
        } else {
            const UINT8* end;
            end = in_end;
            while (ip < end && *m_pos == *ip)
                m_pos++, ip++;
            m_len = (UINT32)(ip - ii);

            if (m_len < 3)
                return STATUS_INTERNAL_ERROR;

            if (m_off <= M3_MAX_OFFSET) {
                m_off -= 1;
                if (m_len <= 33)
                    *op++ = LZO_BYTE(M3_MARKER | (m_len - 2));
                else {
                    m_len -= 33;
                    *op++ = M3_MARKER | 0;
                    goto m3_m4_len;
                }
            } else {
                m_off -= 0x4000;

                if (m_off <= 0 || m_off > 0x7fff)
                    return STATUS_INTERNAL_ERROR;

                if (m_len <= 9)
                    *op++ = LZO_BYTE(M4_MARKER | ((m_off & 0x4000) >> 11) | (m_len - 2));
                else {
                    m_len -= 9;
                    *op++ = LZO_BYTE(M4_MARKER | ((m_off & 0x4000) >> 11));
m3_m4_len:
                    while (m_len > 255) {
                        m_len -= 255;
                        *op++ = 0;
                    }

                    if (m_len <= 0)
                        return STATUS_INTERNAL_ERROR;

                    *op++ = LZO_BYTE(m_len);
                }
            }

m3_m4_offset:
            *op++ = LZO_BYTE((m_off & 63) << 2);
            *op++ = LZO_BYTE(m_off >> 6);
        }

        ii = ip;
        if (ip >= ip_end)
            break;
        DVAL_FIRST(dv, ip);
    }

    /* store final literal run */
    if (in_end - ii > 0) {
        UINT32 t = (UINT32)(in_end - ii);

        if (op == out && t <= 238)
            *op++ = LZO_BYTE(17 + t);
        else if (t <= 3)
            op[-2] |= LZO_BYTE(t);
        else if (t <= 18)
            *op++ = LZO_BYTE(t - 3);
        else {
            UINT32 tt = t - 18;

            *op++ = 0;
            while (tt > 255) {
                tt -= 255;
                *op++ = 0;
            }

            if (tt <= 0)
                return STATUS_INTERNAL_ERROR;

            *op++ = LZO_BYTE(tt);
        }

        do {
            *op++ = *ii++;
        } while (--t > 0);
    }

    *out_len = (UINT32)(op - out);

    return STATUS_SUCCESS;
}