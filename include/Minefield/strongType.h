#pragma once

template <typename T, typename TagT>
class StrongType
{
public:
    constexpr StrongType(T value): mValue(value) {};
    constexpr T const& raw() { return mValue; }

private:
    T mValue;
};