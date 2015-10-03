#ifndef _QUEUE_
#define _QUEUE_

#include <stdexcept>

template <typename Data>
class queue {

	private:
		int head;
		int tail;
		Data *data;
		int qsize;

		static const int DEF_SIZE = 20;
	public:
		queue(const int _size = DEF_SIZE) : qsize {_size}, head {-1}, tail {-1} {
			if (qsize > 0)
				data = new Data[qsize];
			else
				throw std::invalid_argument("Please provide a size greater than 0.");
		}
		~queue();
		bool push(const Data & _new);
		const Data & pop();
		const Data & front() const;
		const int size() const;
		bool empty() const;
};

// Sorry about this
#include "../src/queue.cpp"

#endif
