# CPP-Multi-Type-Container

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
}
```
Produces the following output:
``Foobar``
