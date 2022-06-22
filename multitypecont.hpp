#include <vector>
#include <unordered_map>
#include <memory>
#include "../tools/constexpr-typehashing.hpp"

struct Base {};

template<typename T, class Container = std::vector<T>>
struct Cont : public Base
{
    using Container_t = Container;

    Container_t _data;
    auto& get() { return _data; }

    void push_back(T val) { _data.push_back(val); }
};

// class that can hold vectors of multiple types
class MultiTypeContainer
{
protected:
    std::unordered_map<size_t, std::shared_ptr<Base>> _vectors;

    template<typename T> struct hash_t final { inline static const size_t value { typehash::hash_code<T>() }; };
public:
    // will attempt to make a new vector of type T if T does not exist yet
    template<typename T> void add(T val)
    {
        const auto h = hash_t<T>::value;       

        if (_vectors.find(h) == _vectors.end())
            _vectors.insert({h, std::make_shared<Cont<T>>()});
        
        std::static_pointer_cast<Cont<T>>(_vectors[h])->push_back(val);
    }

    // returns: shared_ptr<std::vector<T>>
    template<typename T> auto& get()
    {
        return std::static_pointer_cast<Cont<T>>(_vectors[hash_t<T>::value])->get();
    }
};
