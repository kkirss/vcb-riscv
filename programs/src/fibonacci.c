int _start() {
    int i;
    int n = 100;
    int t1 = 0;
    int t2 = 1;
    int nextTerm = t1 + t2;

    for (i = 3; i <= n; ++i) {
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }

    return 0;
}

