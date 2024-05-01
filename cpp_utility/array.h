#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <limits>
#include <ranges>
#include <type_traits>
#include <xtr1common>

template<typename Type, std::size_t Size>
class Array final : public std::array<Type, Size> {
public:
    [[nodiscard]] constexpr auto find_first_not_of(const Type value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::enumerate ) {
            if ( data != value ) {
                return std::size_t { index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_first_of(const Type value) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::enumerate ) {
            if ( data == value ) {
                return std::size_t { index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_last_not_of(const Type value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::reverse
                  | std::ranges::views::enumerate ) {
            if ( data != value ) {
                return std::size_t { Size - 1 - index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_last_of(const Type value) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::reverse
                  | std::ranges::views::enumerate ) {
            if ( data == value ) {
                return std::size_t { Size - 1 - index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find(const Type value) const noexcept -> std::size_t {
        return find_first_of(value);
    }

    [[nodiscard]] constexpr auto rfind(const Type value) const noexcept -> std::size_t {
        return find_last_of(value);
    }
};

template<typename Arg, typename... Args>
Array(Arg, Args...) -> Array<Arg, 1 + sizeof...(Args)>;
