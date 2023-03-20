int main() {
    int n = 46;

    int t1 = 0;
    int t2 = 0;
    int nextTerm = 1;

    for (int i = 2; i <= n; ++i) {
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }

    return nextTerm;
}
