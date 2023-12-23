int calculate_fibonacci_term(int n) {
    int t1 = 0;
    int t2 = 0;
    int next_term = 1;

    for (int i = 2; i <= n; ++i) {
        t1 = t2;
        t2 = next_term;
        next_term = t1 + t2;
    }

    return next_term;
}
