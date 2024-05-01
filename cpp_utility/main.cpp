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

    auto arr = Array<int, 10> {};

    arr = Array { 10, 5, 6, 3, 1, 4, 2, 7, 8, 9 };
    sort::bubble(std::span { arr });
    for ( const auto _ : arr ) {
        std::cout << _ << ", ";
    }
    std::cout << std::endl;

    arr = Array { 10, 5, 6, 3, 1, 4, 2, 7, 8, 9 };
    sort::selection(std::span { arr });
    for ( const auto _ : arr ) {
        std::cout << _ << ", ";
    }
    std::cout << std::endl;

    return int { 0 };
}
