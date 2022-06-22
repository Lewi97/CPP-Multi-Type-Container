#include <vector>
#include <unordered_map>
#include <memory>
#include "../tools/constexpr-typehashing.hpp"

#define REGISTER_TYPE_CONTAINER(TYPE, CONTAINER) template<> struct container_hint<TYPE> final { using container_t = CONTAINER; };
#define CONTAINER_TYPE typename container_hint<T>::container_t

namespace experimental
{
struct Base {};

template<typename T, class Container = std::vector<T>>
struct Cont : public Base
{
    using Container_t = Container;

    Container_t _data;
    auto& get() { return _data; }

    void push_back(T val) { _data.push_back(val); }
};

// stores container type of type T
template<typename T> struct container_hint final { using container_t = std::vector<T>; };

// Multiclass container allowing of storing multiple classes in different containers
// linking a type to a specific container can be done by calling namespace experimental { REGISTER_TYPE_CONTAINER(value_type, container<value_type>) }
class MultiTypeContainer
{
protected:
    std::unordered_map<size_t, std::shared_ptr<Base>> _vectors;

    template<typename T> struct hash_t final { inline static const size_t value { typehash::hash_code<T>() }; };
public:
    template<typename T>
    void add(T val)
    {
        const auto h = hash_t<T>::value;       

        if (_vectors.find(h) == _vectors.end())
            _vectors.insert({h, std::make_shared<Cont<T, CONTAINER_TYPE>>()});
        
        std::static_pointer_cast<Cont<T, CONTAINER_TYPE>>(_vectors[h])->push_back(val);
    }

    template<typename T> auto& get()
    {
        return std::static_pointer_cast<Cont<T, CONTAINER_TYPE>>(_vectors[hash_t<T>::value])->get();
    }
};
} // namespace experimental