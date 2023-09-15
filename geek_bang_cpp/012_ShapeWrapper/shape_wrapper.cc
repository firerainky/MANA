#include "shape.h"

// These code is from: https://time.geekbang.org/column/article/169225

class ShapeWrapper {
public:
    explicit ShapeWrapper(Shape *ptr = nullptr) : ptr_(ptr) {}
    ~ShapeWrapper() { delete ptr_; }
    Shape *get() const { return ptr_; }

private:
    Shape *ptr_;
};

void foo() { ShapeWrapper ptr_wrapper(create_shape(shape_type::Circle)); }

template<typename T>
class smart_ptr {
public:
    explicit smart_ptr(T *ptr = nullptr) : ptr_(ptr) {}
    ~smart_ptr() { delete ptr_; }

    // Disable copy constructor and copy-assignment operator
    // smart_ptr(const smart_ptr &) = delete;
    // smart_ptr &operator=(const smart_ptr &) = delete;

    template<typename U>
    smart_ptr(smart_ptr<U> &&other) {
        ptr_ = other.release();
    }
    smart_ptr(smart_ptr &&other) { ptr_ = other.release(); }
    smart_ptr &operator=(smart_ptr rhs) {
        rhs.swap(*this);
        return *this;
    }

    T *release() {
        T *ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }

    T *get() const { return ptr_; }
    T &operator*() const { return *ptr_; }
    T *operator->() const { return ptr_; }

    operator bool() const { return ptr_; }

private:
    T *ptr_;
};

int main() {
    // The rect destructor is not called when the program ends.
    // This is a memory leak caused by "object slicing"
    Shape *rect = create_shape(shape_type::Rectangle);
    rect->draw();

    // Using ShapeWrapper will not cause such problem
    // because ShapeWrapper is not allocated on heap but allocated on stack.
    // Then RAII is working to call destructor of Shape
    ShapeWrapper ptr_wrapper(create_shape(shape_type::Triangle));
    ptr_wrapper.get()->draw();
    foo();

    // smart_ptr<Shape> smartP(new Rectangle());
    smart_ptr<Shape> smartP(create_shape(shape_type::Rectangle));
    if (smartP) { puts("Good yep"); }
    smartP->draw();
    (*smartP).draw();

    smart_ptr<Shape> ptr1{create_shape(shape_type::Circle)};
    // smart_ptr<Shape> ptr2{ptr1};
    smart_ptr<Shape> ptr3 = std::move(ptr1);
}