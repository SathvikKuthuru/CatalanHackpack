/**
 * Author: Jacob Steinebronn
 * Date: 2024-02-16
 * License: Unknown
 * Source: Suffix Automaton - a powerful tool for dealing with strings
 * Description: Builds suffix automaton for a string.
 * Time: O(n)
 * Status: not stress-tested
 */

struct st { int len, pos, term; st *link; map<char, st*> next; };
st *suffixAutomaton(string &str) {
    st *last = new st(), *root = last;
    for(auto c : str) {
        st *p = last, *cur = last = new st{last->len + 1, last->len};
        while(p && !p->next.count(c))
            p->next[c] = cur, p = p->link;
        if (!p) cur->link = root;
        else {
            st *q = p->next[c];
            if (p->len + 1 == q->len) cur->link = q;
            else {
                st *clone = new st{p->len+1, q->pos, 0, q->link, q->next};
                for (; p && p->next[c] == q; p = p->link)
                    p->next[c] = clone;
                q->link = cur->link = clone;
            }
        }
    }
    while(last) last->term = 1, last = last->link;
    return root;
}
