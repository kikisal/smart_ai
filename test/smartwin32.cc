#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include "base/generics.hpp"
#include "base/utility.hpp"


struct Shape {

    template<typename... Args>
    Shape(Args&&... args) {
        using namespace generics;
        auto pack = depack_parameters<int>(std::forward<Args&&>(args)...);

        for (int i = 0; i < pack.elements(); ++i)
            dimensions.push_back(pack[i]);
    }

    int operator[] (size_t d) {
        if (d < 0 || d >= dimensions.size())
            return 0;
        
        if (count() <= 0)
            return 0;

        return dimensions[d];
    }

    // return dimension count
    inline float count() const {
        return dimensions.size();
    }

    inline float elements() const {
        if (count() <= 0)
            return 0;

        size_t result = dimensions[0];

        for (int i = 1; i < count(); ++i)
            result *= dimensions[i];

        return result;
    }

private:
    std::vector<int> dimensions;

};

struct Tensor {
    using TensorDataType = float;
    using Tuple = generics::Tuple<int>;

    explicit Tensor() = default;
    Tensor (Shape s) : _shape { s } {
        data.reserve(s.elements());
    };

    //  i*s[1]s[2][3] + j*s[2]s[3] + k*s[3] + l
    TensorDataType const& get(Tuple entries) const {
        auto index = entries.last();

        for (int i = 0; i < entries.elements() - 1; ++i)
            index += entries[i] * utility::indexed_product<float>(entries, i + 1);

        std::cout << "current memory index: " << index << std::endl;

        return 0;
    }

    void zeros() {
        
    }

    Shape const& shape() const {
        return _shape;
    }

private:
    std::vector<TensorDataType> data;
    Shape _shape;
};

struct math {
    static Tensor random(float, float, Shape);
};


float random(float a, float b);


int main() {
    Tensor t = math::random(0, 1, Shape(4, 4));


    return 0;
}

Tensor math::random(float a, float b, Shape shape) {
    Tensor t = Tensor {shape};
    t.zeros();
    t.get(generics::TupleInt(2, 4, 5, 6));
    
}

float random(float a, float b) {
    return 0;
}