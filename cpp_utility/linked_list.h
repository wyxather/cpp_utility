#pragma once

#include <type_traits>
#include <xtr1common>

template<typename>
class LinkedListNode;

template<typename Node>
class LinkedListNodeIterator final {
public:
    Node *node = nullptr;

    [[nodiscard]] constexpr auto operator!=([[maybe_unused]] const LinkedListNodeIterator &end
    ) const noexcept -> bool {
        return node != nullptr;
    }

    constexpr auto operator++() noexcept -> void {
        node = node->next.node;
    }

    [[nodiscard]] constexpr auto operator*() const noexcept -> Node & {
        return *node;
    }

    [[nodiscard]] constexpr auto operator->() const noexcept -> Node * {
        return node;
    }

    [[nodiscard]] constexpr auto valid() const noexcept -> bool {
        return node != nullptr;
    }
};

template<typename Data>
class LinkedListNode final {
public:
    using Iterator = LinkedListNodeIterator<LinkedListNode>;

    Iterator next;
    Data data;

    [[nodiscard]] constexpr auto begin() noexcept -> Iterator {
        return Iterator { this };
    }

    [[nodiscard]] constexpr auto end() noexcept -> Iterator {
        auto it = begin();
        while ( it.node->next.valid() ) {
            ++it;
        }
        return it;
    }

    template<typename... Args>
    constexpr auto emplace_back(Args &&...args) noexcept -> Iterator {
        auto it = end();
        return it.node->next = Iterator {
            new LinkedListNode {
                .next { nullptr },
                .data { std::forward<Args>(args)... },
            },
        };
    }

    constexpr auto put_back(const Iterator new_node) noexcept -> Iterator {
        auto it = end();
        return it.node->next = new_node;
    }

    template<typename... Args>
    constexpr auto emplace(Args &&...args) noexcept -> Iterator {
        return next = Iterator {
            new LinkedListNode {
                .next { next },
                .data { std::forward<Args>(args)... },
            },
        };
    }

    constexpr auto pop_back() noexcept -> Iterator {
        auto it = begin();
        if ( !it.node->next.valid() ) {
            return it;
        }
        while ( it.node->next.node->next.valid() ) {
            ++it;
        }
        delete it.node->next.node;
        it.node->next.node = nullptr;
        return it;
    }

    constexpr auto detach_back() noexcept -> Iterator {
        auto it = begin();
        if ( !it.node->next.valid() ) {
            return it;
        }
        while ( it.node->next.node->next.valid() ) {
            ++it;
        }
        const auto detached_node = it.node->next;
        it.node->next = Iterator {};
        return detached_node;
    }

    constexpr auto pop() noexcept -> Iterator {
        const auto it = begin();
        if ( !next.valid() ) {
            return it;
        }
        const auto new_next_node = next.node->next;
        delete next.node;
        next = new_next_node;
        return it;
    }
};

template<typename Data>
class LinkedList final {
public:
    using Node = LinkedListNode<Data>;
    using NodeIterator = Node::Iterator;

    Node *node;

    [[nodiscard]] constexpr auto empty() const noexcept -> bool {
        return node == nullptr;
    }

    [[nodiscard]] constexpr auto begin() noexcept -> NodeIterator {
        return !empty() ? node->begin() : NodeIterator {};
    }

    [[nodiscard]] constexpr auto end() noexcept -> NodeIterator {
        return !empty() ? node->end() : NodeIterator {};
    }

    template<typename... Args>
    constexpr auto emplace_back(Args &&...args) noexcept -> NodeIterator {
        if ( empty() ) {
            node = new Node {
                .next { nullptr },
                .data { std::forward<Args>(args)... },
            };
            return NodeIterator { node };
        }
        return node->emplace_back(std::forward<Args>(args)...);
    }

    constexpr auto put_back(const NodeIterator new_node) noexcept -> NodeIterator {
        if ( empty() ) {
            node = new_node.node;
            return new_node;
        }
        return node->put_back(new_node);
    }

    constexpr auto pop_back() noexcept -> NodeIterator {
        if ( empty() ) {
            return NodeIterator {};
        }
        if ( !node->next.valid() ) {
            delete node;
            node = nullptr;
            return NodeIterator {};
        }
        return node->pop_back();
    }

    constexpr auto detach_back() noexcept -> NodeIterator {
        if ( empty() ) {
            return NodeIterator {};
        }
        if ( !node->next.valid() ) {
            const auto detached_node = node;
            node = nullptr;
            return NodeIterator { detached_node };
        }
        return node->detach_back();
    }

    constexpr auto reverse() noexcept -> LinkedList & {
        auto reversed = LinkedList<int> {
            .node { std::addressof(*detach_back()) },
        };
        auto reversed_it = NodeIterator { reversed.node };
        while ( !empty() ) {
            reversed_it = reversed_it->put_back(detach_back());
        }
        node = reversed.node;
        return *this;
    }
};
