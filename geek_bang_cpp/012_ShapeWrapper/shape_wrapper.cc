#include <stdexcept>
#include <stdio.h>

// These code is from: https://time.geekbang.org/column/article/169225

enum class shape_type {
    Circle,
    Triangle,
    Rectangle,
};

class Shape {
public:
    virtual ~Shape(){};
};
class Circle : public Shape {
public:
    Circle() { puts("Shape::Circle()"); }
    ~Circle() { puts("~Shape::Circle()"); }
};
class Triangle : public Shape {
public:
    Triangle() { puts("Shape::Triangle()"); }
    ~Triangle() { puts("~Shape::Triangle()"); }
};
class Rectangle : public Shape {
public:
    Rectangle() { puts("Shape::Rectangle()"); }
    ~Rectangle() { puts("~Shape::Rectangle()"); }
};

inline Shape *create_shape(shape_type type) {
    switch (type) {
        case shape_type::Circle:
            return new Circle();
        case shape_type::Triangle:
            return new Triangle();
        case shape_type::Rectangle:
            return new Rectangle();
    }
    throw std::logic_error("shape type is invalid");
}

class ShapeWrapper {
public:
    explicit ShapeWrapper(Shape *ptr = nullptr) : ptr_(ptr) {}
    ~ShapeWrapper() { delete ptr_; }
    Shape *get() const { return ptr_; }

private:
    Shape *ptr_;
};

void foo() { ShapeWrapper ptr_wrapper(create_shape(shape_type::Circle)); }

int main() {
    // The rect destructor is not called when the program ends.
    // This is a memory leak caused by "object slicing"
    Shape *rect = create_shape(shape_type::Rectangle);

    // Using ShapeWrapper will not cause such problem
    // because ShapeWrapper is not allocated on heap but allocated on stack.
    // Then RAII is working to call destructor of Shape
    ShapeWrapper ptr_wrapper(create_shape(shape_type::Triangle));
    foo();
}