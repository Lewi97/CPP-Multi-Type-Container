# A cpp multi type vector

# Adding types
Types can be added with ``push_back`` and ``emplace_back`` which will call the respective function of the underlying vector.

# Retrieving types
Retrieving a container of types can be done with ``get<Type>()``, returning multiple types is also allowed ''get<Type, Type2>()``.

# Examples
```cpp
struct Foo
{
    void invoke() const { std::cout << "Foo"; }
};

struct Bar
{
    void invoke() const { std::cout << "bar"; }
};

int main()
{
    lw::MultiTypeVector core{};

    core.push_back<Foo>(Foo());
    core.push_back<Bar>(Bar());

    core.get<Foo>().begin()->invoke();
    core.get<Bar>().begin()->invoke();

    auto&& [foo, bar] = core.get<Foo, Bar>();
    foo.begin()->invoke();
    bar.begin()->invoke();
}
```
Produces the following output:
``FoobarFoobar``
