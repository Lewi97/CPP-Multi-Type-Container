#ifndef CONSTEXPR_TYPEHASHING_H
#define CONSTEXPR_TYPEHASHING_H

#include <cstddef>
#include <cstdint>
// Adapted from https://gist.github.com/ktf/b51547b25f6467b2fb352d239b6080e2

namespace hashers
{
    struct fnv1a
    {
    protected:
        constexpr static uint64_t fnv_basis {14695981039346656037ull};
        constexpr static uint64_t fnv_prime {1099511628211ull};
    public:
        constexpr static 
        uint64_t hash(std::size_t n, const char *str, uint64_t _hash = fnv_basis)
        {
            return n > 0 ? hash(n - 1, str + 1, (_hash ^ *str) * fnv_prime) : _hash;
        }
    };
}

struct typehash
{
protected:
    struct cstring // somehow this gets around the fact that __pretty_func___ cannot be interpreted as string literal
    {
        const char* str{};
        const size_t len{};

        template<size_t N> constexpr
        cstring(const char(&str)[N])
            : str(str)
            , len(N - 1)
        {}

        constexpr size_t hash() const 
        { return hashers::fnv1a::hash(len, str);}

        friend std::ostream& operator<<(std::ostream& out, const cstring& str)
        {
            out << str.str;
            return out;
        }
    };
public:
    template<typename T>
    constexpr static cstring type_name()
    {
        return {__PRETTY_FUNCTION__};
    }

    template <typename TYPE>
    constexpr static size_t hash_code()
    {
        constexpr auto h = type_name<TYPE>().hash();
        return h;
    }
};

#endif // CONSTEXPR_TYPEHASHING_H
