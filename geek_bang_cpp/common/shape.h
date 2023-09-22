#ifndef SHAPE_H
#define SHAPE_H

#include <stdexcept>
#include <stdio.h>

enum class shape_type {
    Circle,
    Triangle,
    Rectangle,
};

class Shape {
public:
    virtual ~Shape(){};
    virtual void draw(){};
};
class Circle : public Shape {
public:
    Circle() { puts("Shape::Circle()"); }
    ~Circle() { puts("~Shape::Circle()"); }
    void draw() { puts("Draw Shape::Circle()"); }
};
class Triangle : public Shape {
public:
    Triangle() { puts("Shape::Triangle()"); }
    ~Triangle() { puts("~Shape::Triangle()"); }
    void draw() { puts("Draw Shape::Triangle()"); }
};
class Rectangle : public Shape {
public:
    Rectangle() { puts("Shape::Rectangle()"); }
    ~Rectangle() { puts("~Shape::Rectangle()"); }
    void draw() { puts("Draw Shape::Rectangle()"); }
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

class Result {
public:
    Result() { puts("Result::Result()"); }
    ~Result() { puts("~Result::Result()"); }
    inline void doSomething() { puts("Result::doSomething()"); }
};

inline Result process_shape(const Shape &shape1, const Shape &shape2) {
    puts("process_shape()");
    return Result();
}

#endif