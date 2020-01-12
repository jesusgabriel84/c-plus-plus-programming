const int kMaxReferenceCount = 3;

class RestrictedRefCounter {
public:
	RestrictedRefCounter() : count_(0) {}
	
	bool Increment() {
		if(count_ < kMaxReferenceCount) {
			count_++;
			return true;
		}
		return false;
	}
	void Reset() {  count_ = 1; }
	int Decrement() { return --count_; }
	int GetCount() { return count_; }

private:
	int count_;
};
