#pragma once

template<typename T>
class tsqueue
{
		
		public:
			tsqueue() = default;
			tsqueue(const tsqueue<T>&) = delete;
			virtual ~tsqueue() { clear(); }

		public:

			// Removes and returns item from front of Queue
			T pop_front()
			{
				std::unique_lock <std::mutex> lock (muxQueue);
				auto t = std::move(deqQueue.front());
				deqQueue.pop_front();
				return t;
			}

			// Adds an item to back of Queue
			void push_back(const T& item)
			{
				std::unique_lock <std::mutex> lock (muxQueue);
				deqQueue.emplace_back(std::move(item));

				std::unique_lock<std::mutex> ul(muxBlocking);
				cvBlocking.notify_one();
			}


			// Returns true if Queue has no items
			bool empty()
			{
				std::unique_lock <std::mutex> lock (muxQueue);
				return deqQueue.empty();
			}

			// Clears Queue
			void clear()
			{
				std::unique_lock <std::mutex> lock (muxQueue);
				deqQueue.clear();
			}

			void wait()
			{
				while (empty())
				{
					std::unique_lock <std::mutex> lock (muxQueue);
					cvBlocking.wait(lock);
				}
			}
			
			protected:
			std::mutex muxQueue;
			std::deque<T> deqQueue;
			std::condition_variable cvBlocking;
			std::mutex muxBlocking;

};
