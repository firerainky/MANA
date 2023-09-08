template<typename T>
class Hero {
public:
    Hero() : data_(new T()){};
    void superpower();

private:
    T *data_;
};