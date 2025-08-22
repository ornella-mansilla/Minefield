#pragma once
#include <type_traits>
#include <functional>

template <typename T, typename TagT>
class StrongType
{
public:
    constexpr explicit StrongType(T value): mValue(initValue(value)){}

    constexpr T raw() const
    {
        if constexpr (std::is_reference_v<T>)
        {
            return mValue.get();
        }
        else
        {
            return mValue;
        }
    }

private:
    using StorageType = std::conditional_t<std::is_reference_v<T>, std::reference_wrapper<std::remove_reference_t<T>>, T>;
    StorageType mValue;

    static constexpr StorageType initValue(T value)
    {
        if constexpr (std::is_reference_v<T>)
        {
            return std::ref(value);
        }
        else
        {
            return value;
        }
    }
};

