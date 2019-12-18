__attribute__((used)) static int safe_atou_optional_plus(const char *s, unsigned *ret) {
        const char *p;
        int r;

        assert(s);
        assert(ret);

        /* Returns 1 if plus, 0 if no plus, negative on error */

        p = endswith(s, "+");
        if (p)
                s = strndupa(s, p - s);

        r = safe_atou(s, ret);
        if (r < 0)
                return r;

        return !!p;
}