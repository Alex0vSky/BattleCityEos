#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
// @insp SO/how-to-check-if-enum-value-is-valid
namespace net {
template<typename EnumType, EnumType... Values>
class EnumCheck;

template<typename EnumType>
class EnumCheck<EnumType>
{
public:
    template<typename IntType>
    static bool constexpr isValue(IntType) { return false; }
};
template<typename EnumType, EnumType V, EnumType... Next>
class EnumCheck<EnumType, V, Next...> : private EnumCheck<EnumType, Next...>
{
    using super = EnumCheck<EnumType, Next...>;

public:
    template<typename IntType>
    static bool constexpr isValue(IntType v)
    {
        return v == static_cast<IntType>(V) || super::isValue(v);
    }
};
} // namespace net
