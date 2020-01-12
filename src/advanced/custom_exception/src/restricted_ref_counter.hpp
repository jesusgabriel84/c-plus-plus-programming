// copy your implementation from the last round here (if you had one and used it)
// and wrap it inside a WeirdMemoryAllocator namespace

//	const int kMaxReferenceCount = 3;

namespace WeirdMemoryAllocator
{



	class RestrictedRefCounter {
	public:
		RestrictedRefCounter() : count_(0) {}
		
		bool Increment() {
			if(count_ < 3) {
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

}
