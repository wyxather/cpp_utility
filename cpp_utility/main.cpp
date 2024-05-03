#include <iostream>

#include "array.h"
#include "linked_list.h"
#include "string.h"

namespace sort {

    template<typename Type, std::size_t Size>
    constexpr auto bubble(Array<Type, Size> &data) noexcept {
        auto last_index = Size - 1;
        for ( ; last_index > 0; --last_index ) {
            for ( auto i = std::size_t { 0 }; i < last_index; ++i ) {
                if ( data[i] > data[i + 1] ) {
                    std::swap(data[i], data[i + 1]);
                }
            }
        }
    }

    template<typename Type>
    constexpr auto bubble(std::span<Type> span) noexcept {
        if ( span.empty() ) {
            return;
        }
        const auto size = span.size();
        for ( auto [index, value] : span | std::ranges::views::enumerate ) {
            if ( index >= size - 1 ) {
                break;
            }
            auto &next_value = span[index + 1];
            if ( value > next_value ) {
                std::swap(value, next_value);
            }
        }
        return bubble(std::span<Type> { span.begin(), std::prev(span.end()) });
    }

    template<typename Type, std::size_t Size>
    constexpr auto selection(Array<Type, Size> &data) noexcept {
        for ( auto [index, value] : data | std::ranges::views::enumerate ) {
            if ( index >= Size - 1 ) {
                break;
            }
            auto smallest = std::addressof(value);
            for ( auto i = index + 1; i < Size; ++i ) {
                auto &other_value = data[i];
                if ( *smallest > other_value ) {
                    smallest = std::addressof(other_value);
                }
            }
            if ( smallest != std::addressof(value) ) {
                std::swap(value, *smallest);
            }
        }
    }

    template<typename Type>
    constexpr auto selection(std::span<Type> span) noexcept {
        const auto size = span.size();
        for ( auto [index, value] : span | std::ranges::views::enumerate ) {
            if ( index >= size - 1 ) {
                break;
            }
            auto smallest = std::addressof(value);
            for ( auto &other_value :
                  std::span<Type> { span.begin() + index + 1, span.end() } ) {
                if ( *smallest > other_value ) {
                    smallest = std::addressof(other_value);
                }
            }
            if ( smallest != std::addressof(value) ) {
                std::swap(value, *smallest);
            }
        }
    }

}  // namespace sort

//"12321"
template<typename Type>
constexpr auto find_longest_palindrome(std::span<Type> str) noexcept -> std::span<Type> {
    auto longest_palindrome = std::span<Type> { str.begin(), str.begin() + 1 };
    for ( auto it = str.begin() + 1; it != str.end(); ++it ) {
        constexpr auto palindrom_count = [](std::span<Type> left_span, std::span<Type> right_span
                                         ) noexcept -> std::size_t {
            const auto spans =
                std::ranges::views::zip(std::ranges::views::reverse(left_span), right_span);
            auto count = std::size_t { 0 };
            for ( const auto [l, r] : spans ) {
                if ( l == r ) {
                    ++count;
                } else {
                    break;
                }
            };
            return count;
        };
        constexpr auto clamp_span = [](std::span<Type> &left_span,
                                       std::span<Type> &right_span) noexcept -> void {
            if ( right_span.size() > left_span.size() ) {
                right_span = std::span<Type> {
                    right_span.begin(),
                    left_span.size(),
                };
            } else if ( left_span.size() > right_span.size() ) {
                left_span = std::span<Type> {
                    left_span.begin() + (left_span.size() - right_span.size()),
                    right_span.size(),
                };
            }
        };
        auto left_span = std::span<Type> { str.begin(), it };
        auto right_span = std::span<Type> { it, str.end() };
        clamp_span(left_span, right_span);
        auto count = palindrom_count(left_span, right_span);
        if ( longest_palindrome.size() < count * 2 ) {
            longest_palindrome = std::span<Type> {
                std::addressof(*(left_span.begin() + left_span.size() - count)),
                count * 2,
            };
            std::cout << "[]"
                      << std::string_view { longest_palindrome.begin(),
                                            longest_palindrome.end() }
                      << std::endl;
        }
        left_span = std::span<Type> { str.begin(), it };
        right_span = std::span<Type> { it + 1, str.end() };
        clamp_span(left_span, right_span);
        count = palindrom_count(left_span, right_span);
        if ( longest_palindrome.size() < count * 2 + 1 ) {
            longest_palindrome = std::span<Type> {
                std::addressof(*(left_span.begin() + left_span.size() - count)),
                count * 2 + 1,
            };
            //std::cout << "[]"
            //          << std::string_view { longest_palindrome.begin(),
            //                                longest_palindrome.end() }
            //          << std::endl;
        }

        //std::cout << ":" << *it << std::endl;

        //for ( const auto l : left_span ) {
        //    std::cout << l;
        //}
        //std::cout << std::endl;

        //for ( const auto r : right_span ) {
        //    std::cout << r;
        //}
        //std::cout << std::endl;

        //std::cout << std::endl;
    }
    return longest_palindrome;
}

auto main() -> int {
    //auto linked_list = LinkedList<int> {};
    //linked_list.emplace_back(1);
    //linked_list.emplace_back(2);
    //linked_list.emplace_back(3);
    //linked_list.emplace_back(4);
    //for ( const auto &node : linked_list ) {
    //    std::cout << "[O] " << (void *)&node << " | " << node.data << std::endl;
    //}
    //linked_list.reverse();
    //for ( const auto &node : linked_list ) {
    //    std::cout << "[R] " << (void *)&node << " | " << node.data << std::endl;
    //}

    //auto arr = Array<int, 10> {};

    //arr = Array { 10, 5, 6, 3, 1, 4, 2, 7, 8, 9 };
    //sort::bubble(std::span { arr });
    //for ( const auto _ : arr ) {
    //    std::cout << _ << ", ";
    //}
    //std::cout << std::endl;

    //arr = Array { 10, 5, 6, 3, 1, 4, 2, 7, 8, 9 };
    //sort::selection(std::span { arr });
    //for ( const auto _ : arr ) {
    //    std::cout << _ << ", ";
    //}
    //std::cout << std::endl;

    constexpr auto str = std::string_view { "abc" };
    std::cout << std::string_view {
        find_longest_palindrome(std::span { str.begin(), str.end() })
    } << std::endl;
    return int { 0 };
}
