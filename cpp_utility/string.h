#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <limits>
#include <ranges>
#include <type_traits>
#include <xtr1common>

template<typename, std::size_t>
class String;

template<std::size_t Size>
class String<char, Size> final : public std::array<char, Size> {
public:
    [[nodiscard]] constexpr auto find_first_not_of(const char value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::enumerate ) {
            if ( index >= Size - 1 ) {
                break;
            }
            if ( data != value ) {
                return std::size_t { index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_first_of(const char value) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::enumerate ) {
            if ( index >= Size - 1 ) {
                break;
            }
            if ( data == value ) {
                return std::size_t { index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_last_not_of(const char value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::reverse
                  | std::ranges::views::enumerate | std::ranges::views::drop(1) ) {
            if ( data != value ) {
                return std::size_t { Size - 1 - index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_last_of(const char value) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::reverse
                  | std::ranges::views::enumerate | std::ranges::views::drop(1) ) {
            if ( data == value ) {
                return std::size_t { Size - 1 - index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find(const char value) const noexcept -> std::size_t {
        return find_first_of(value);
    }

    [[nodiscard]] constexpr auto rfind(const char value) const noexcept -> std::size_t {
        return find_last_of(value);
    }
};

template<std::size_t Size>
class String<wchar_t, Size> final : public std::array<wchar_t, Size> {
public:
    [[nodiscard]] constexpr auto find_first_not_of(const wchar_t value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::enumerate ) {
            if ( index >= Size - 1 ) {
                break;
            }
            if ( data != value ) {
                return std::size_t { index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_first_of(const wchar_t value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::enumerate ) {
            if ( index >= Size - 1 ) {
                break;
            }
            if ( data == value ) {
                return std::size_t { index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_last_not_of(const wchar_t value
    ) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::reverse
                  | std::ranges::views::enumerate | std::ranges::views::drop(1) ) {
            if ( data != value ) {
                return std::size_t { Size - 1 - index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find_last_of(const wchar_t value) const noexcept -> std::size_t {
        for ( const auto [index, data] : *this | std::ranges::views::reverse
                  | std::ranges::views::enumerate | std::ranges::views::drop(1) ) {
            if ( data == value ) {
                return std::size_t { Size - 1 - index };
            }
        }
        return std::size_t { std::numeric_limits<std::size_t>::max() };
    }

    [[nodiscard]] constexpr auto find(const wchar_t value) const noexcept -> std::size_t {
        return find_first_of(value);
    }

    [[nodiscard]] constexpr auto rfind(const wchar_t value) const noexcept -> std::size_t {
        return find_last_of(value);
    }
};

template<typename Type, std::size_t Size>
    requires(std::same_as<Type, char> || std::same_as<Type, wchar_t>)
String(const Type (&)[Size]) -> String<Type, Size>;

template<typename Arg, typename... Args>
    requires((std::same_as<Arg, char> || std::same_as<Arg, wchar_t>)
             && std::conjunction_v<std::is_same<Arg, Args>...>)
String(Arg, Args...) -> String<Arg, 1 + sizeof...(Args)>;
