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
    MultiTypeContainer core;
    
    core.add<Foo>(Foo());
    core.add<Bar>(Bar());
    
    core.get<Foo>().begin()->invoke();
    core.get<Bar>().begin()->invoke();
}
```
Produces the following output:
``Foobar``
