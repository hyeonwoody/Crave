#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <queue> 
  
// Thread-safe queue 
template <typename T> 
class ThreadSafeQueue { 
private: 
    // Underlying queue 
    std::queue<T> m_queue; 
  
    // mutex for thread synchronization 
    std::mutex m_mutex; 
  
    // Condition variable for signaling 
    std::condition_variable m_cond; 
  
public: 
    // Pushes an element to the queue 
    void push(T item) 
    { 
  
        // Acquire lock 
        std::unique_lock<std::mutex> lock(m_mutex); 
  
        // Add item 
        m_queue.push(item); 
  
        // Notify one thread that 
        // is waiting 
        m_cond.notify_one(); 
    } 
    
    T front()
    {
        std::unique_lock<std::mutex> lock(m_mutex); 
        m_cond.wait(lock, 
                    [this]() { return !m_queue.empty(); }); 
        T item = m_queue.front();
        return item;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    // Pops an element off the queue 
    void pop() 
    { 
        std::unique_lock<std::mutex> lock(m_mutex); 
  
        m_cond.wait(lock, 
                    [this]() { return !m_queue.empty(); }); 
        m_queue.pop();
    } 
}; 