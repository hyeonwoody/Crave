#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <map> 
  
// Thread-safe queue 
template <typename Key, typename Value> 
class ThreadSafeMap { 
private: 

    std::map<Key, Value> m_map; 
    std::mutex m_mutex; 
    std::condition_variable m_cond; 
  
public: 
    void insert(const std::pair<const Key&, const Value&> keyValue) 
    { 
  
        std::unique_lock<std::mutex> lock(m_mutex); 
  
        m_map[keyValue.first] = keyValue.second; 
    } 
    typename std::map<Key, Value>::const_iterator find(const Key& key) {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_map.find(key);
    }

    typename std::map<Key, Value>::const_iterator end() {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_map.end();
    }
    // Pops an element off the queue 
    bool empty() 
    { 
  
        // acquire lock 
        std::unique_lock<std::mutex> lock(m_mutex); 
  
        return m_map.empty(); 
    } 
}; 