#pragma once

namespace generics {

    template <typename T>
    struct Tuple {

        template<typename... Args>
        Tuple(Args&&... args) {
            using namespace generics;
            auto pack = depack_parameters<T>(std::forward<Args&&>(args)...);

            for (int i = 0; i < pack.elements(); ++i)
                add(pack[i]);
        }

        void add(T const& p) {
            data.push_back(p);
        }

        void add(T&& p) {
            data.push_back(std::move(p));
        }

        T const& last() const {
            return data[elements() - 1];
        }

        size_t elements() const {
            return data.size();
        }

        const T& operator[](size_t index) const {
            if (index < 0 || index >= data.size())
                throw;

            return data[index];
        }

    private:
        std::vector<T> data;
    };

    using TupleInt = Tuple<int>;
        
    template<typename T>
    struct Pack : public Tuple<T> {
        Pack() = default;
    };

    template<typename ET>
    inline void depack_parameters_impl(Pack<ET>& pack) {  }
    
    template<typename ET, typename Arg, typename... Args>
    auto depack_parameters_impl(Pack<ET>& pack, Arg&& arg, Args&&... args) {
        pack.add(std::forward<Arg&&>(arg));
        depack_parameters_impl(pack, std::forward<Arg&&>(args)...);

        return pack;
    }

    
    template<typename ET, typename Arg, typename... Args>
    auto depack_parameters(Arg&& arg, Args&&... args) {
        Pack<ET> pack;
        
        pack.add(std::forward<Arg&&>(arg));

        depack_parameters_impl(pack,
            std::forward<Args&&>(args)...
        );
        return pack;
    }
}
