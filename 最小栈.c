class MinStack {
public:
	stack<int> st;
	stack<int> Minst;
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		if (Minst.empty() || x <= Minst.top())
			Minst.push(x);
		st.push(x);
	}

	void pop() {
		if (st.top() == Minst.top())
			Minst.pop();
		st.pop();
	}

	int top() {
		return st.top();

	}

	int getMin() {
		return Minst.top();
	}
};