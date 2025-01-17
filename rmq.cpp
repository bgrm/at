// https://codeforces.com/blog/entry/78931

#include "comon.h"

int RMQ::op(int x, int y) {
	return v[x] < v[y] ? x : y;
}
// least significant set bit

int RMQ::lsb(int x) {
	return x & -x;
}
// index of the most significant set bit

int RMQ::msb_index(int x) {
	return __builtin_clz(1)-__builtin_clz(x);
}
// answer query of v[r-size+1..r] using the masks, given size <= b

int RMQ::small(int r, int size = b) {
	// get only 'size' least significant bits of the mask
	// and then get the index of the msb of that
	int dist_from_r = msb_index(mask[r] & ((1<<size)-1));

	return r - dist_from_r;
}

void RMQ::init(const vector<int>& v_) { //: v(v_), n(v.size()), mask(n), t(n) {
	v = v_; n = v.size(); mask.resize(n); t.resize(n);
	int curr_mask = 0;
	for (int i = 0; i < n; i++) {

		// shift mask by 1, keeping only the 'b' least significant bits
		curr_mask = (curr_mask<<1) & ((1<<b)-1);

		while (curr_mask > 0 and op(i, i - msb_index(lsb(curr_mask))) == i) {
			// current value is smaller than the value represented by the
			// last 1 in curr_mask, so we need to turn off that bit
			curr_mask ^= lsb(curr_mask);
		}
		// append extra 1 to the mask
		curr_mask |= 1;

		mask[i] = curr_mask;
	}

	// build sparse table over the n/b blocks
	// the sparse table is linearized, so what would be at
	// table[j][i] is stored in table[(n/b)*j + i]
	for (int i = 0; i < n/b; i++) t[i] = small(b*i+b-1);
	for (int j = 1; (1<<j) <= n/b; j++) for (int i = 0; i+(1<<j) <= n/b; i++)
		t[n/b*j+i] = op(t[n/b*(j-1)+i], t[n/b*(j-1)+i+(1<<(j-1))]);
}
// query(l, r) returns the actual minimum of v[l..r]
// to get the index, just change the first and last lines of the function

int RMQ::query(int l, int r) {
	// query too small
	if (r-l+1 <= b) return v[small(r, r-l+1)];

	// get the minimum of the endpoints
	// (there is no problem if the ranges overlap with the sparse table query)
	int ans = op(small(l+b-1), small(r));

	// 'x' and 'y' are the blocks we need to query over
	int x = l/b+1, y = r/b-1;

	if (x <= y) {
		int j = msb_index(y-x+1);
		ans = op(ans, op(t[n/b*j+x], t[n/b*j+y-(1<<j)+1]));
	}

	return v[ans];
}	
	
