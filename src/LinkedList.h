#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

    template<typename Type>
    class LinkedList
    {
        public:
            using difference_type = std::ptrdiff_t;
            using size_type = std::size_t;
            using value_type = Type;
            using pointer = Type*;
            using reference = Type&;
            using const_pointer = const Type*;
            using const_reference = const Type&;

            class LinkedListElement;
            class ConstIterator;
            class Iterator;
            using element = LinkedListElement;
            using element_pointer = LinkedListElement*;
            using const_element_pointer = const LinkedListElement*;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

        private:
            element_pointer head;
            element_pointer tail;
            size_type size;

            void eraseAll() {
                for (auto it = begin(); it != end(); it++) {
                    head = it.current->next;
                    delete it.current;
                    size--;
                }
            }

        public:
            LinkedList() :
                    head(nullptr), tail(nullptr), size(0) {
            }

            LinkedList(std::initializer_list<value_type> l) :
                    LinkedList() {
                for (auto it = std::begin(l); it != std::end(l); ++it) {
                    append(*it);
                }
            }

            LinkedList(const LinkedList& other) :
                    LinkedList() {
                *this = other;
            }

            LinkedList(LinkedList&& other) :
                    head(other.head), tail(other.tail), size(other.size) {
                other.head = nullptr;
                other.tail = nullptr;
                other.size = 0;
            }

            ~LinkedList() {
            }

            LinkedList& operator=(const LinkedList& other) {
                if (this != &other) {
                    eraseAll();
                    for (auto it = other.begin(); it != other.end(); it++) {
                        append(it.current->item);
                    }
                }
                return *this;
            }

            LinkedList& operator=(LinkedList&& other) {
                if (this != &other) {
                    eraseAll();
                    head = other.head;
                    tail = other.tail;
                    size = other.size;
                    other.head = nullptr;
                    other.tail = nullptr;
                    other.size = 0;
                }
                return *this;
            }

            bool isEmpty() const {
                if (size == 0) {
                    return true;
                } else {
                    return false;
                }
            }

            size_type getSize() const {
                return size;
            }

            void append(const_reference item) {
                if (isEmpty()) {
                    head = new element(item, nullptr, nullptr);
                    tail = head;
                    size++;
                } else {
                    tail->next = new element(item, tail, nullptr);
                    tail = tail->next;
                    size++;
                }
            }

            void prepend(const_reference item) {
                if (isEmpty()) {
                    head = new element(item, nullptr, nullptr);
                    tail = head;
                    size++;
                } else {
                    head->previous = new element(item, nullptr, head);
                    head = head->previous;
                    size++;
                }

            }

            void insert(
                    const const_iterator& insertPosition,
                    const_reference item) {
                if (insertPosition == begin()) {
                    prepend(item);
                } else if (insertPosition == end()) {
                    append(item);
                } else {
                    iterator it = insertPosition;
                    it.current->previous->next = new element(
                            item,
                            it.current->previous,
                            it.current->previous->next);
                    it.current->next->previous->previous = it.current->previous
                            ->next;
                }
            }

            value_type popFirst() {
                iterator first = begin();
                value_type firstItem = *first;
                erase(first);
                return firstItem;
            }

            value_type popLast() {
                iterator last = end() - 1;
                value_type lastItem = *last;
                erase(last);
                return lastItem;
            }

            void erase(const const_iterator& position) {
                if (isEmpty() || position == end()) {
                    throw std::out_of_range("erase");
                }
                if (size == 1) {
                    head = nullptr;
                    tail = nullptr;
                    size = 0;
                    delete position.current;
                    return;
                } else if (position == begin()) {
                    head = position.current->next;
                    position.current->next->previous = nullptr;
                } else if (position == end() - 1) {
                    tail = position.current->previous;
                    position.current->previous->next = nullptr;
                } else {
                    position.current->previous->next = position.current->next;
                    position.current->next->previous = position.current
                            ->previous;
                }
                delete position.current;
                size--;
            }

            void erase(
                    const const_iterator& firstIncluded,
                    const const_iterator& lastExcluded) {
                if (isEmpty()) {
                    throw std::out_of_range("erase");
                }
                iterator temp;
                iterator it = firstIncluded;
                while (it != lastExcluded) {
                    if (size == 1) {
                        head = nullptr;
                        tail = nullptr;
                        size = 0;
                        delete it.current;
                        return;
                    } else if (it == begin()) {
                        head = it.current->next;
                        it.current->next->previous = nullptr;
                    } else if (it == end() - 1) {
                        tail = it.current->previous;
                        it.current->previous->next = nullptr;
                    } else {
                        it.current->previous->next = it.current->next;
                        it.current->next->previous = it.current->previous;
                    }
                    temp = it + 1;
                    delete it.current;
                    it = temp;
                    size--;
                }
            }

            iterator begin() {
                iterator it;
                it.current = head;
                it.list = this;
                return it;
            }

            iterator end() {
                iterator it;
                it.current = nullptr;
                it.list = this;
                return it;
            }

            const_iterator cbegin() const {
                iterator it;
                it.current = head;
                it.list = this;
                return it;
            }

            const_iterator cend() const {
                iterator it;
                it.current = nullptr;
                it.list = this;
                return it;
            }

            const_iterator begin() const {
                return cbegin();
            }

            const_iterator end() const {
                return cend();
            }
    }
    ;

    template<typename Type>
    class LinkedList<Type>::LinkedListElement
    {
        public:
            using value_type = typename LinkedList::value_type;
            using element_pointer = typename LinkedList::element_pointer;

            value_type item;
            element_pointer previous;
            element_pointer next;

            LinkedListElement(
                    value_type item,
                    element_pointer previous,
                    element_pointer next) :
                    item(item), previous(previous), next(next) {
            }
    };

    template<typename Type>
    class LinkedList<Type>::ConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename LinkedList::value_type;
            using difference_type = typename LinkedList::difference_type;
            using element_pointer = typename LinkedList::const_element_pointer;
            using reference = typename LinkedList::const_reference;

            element_pointer current;
            const LinkedList* list;

            explicit ConstIterator() :
                    current(nullptr), list(nullptr) {
            }

            reference operator*() const {
                if (list->isEmpty()) {
                    throw std::out_of_range("operator*");
                }
                return current->item;
            }

            ConstIterator& operator++() {
                if (*this == list->end()) {
                    throw std::out_of_range("operator++");
                }
                current = current->next;
                return *this;
            }

            ConstIterator operator++(int) {
                if (*this == list->end()) {
                    throw std::out_of_range("operator++");
                }
                ConstIterator it = *this;
                current = current->next;
                return it;
            }

            ConstIterator& operator--() {
                if (*this == list->begin()) {
                    throw std::out_of_range("operator--");
                } else if (!list->isEmpty() && current == nullptr) {
                    current = list->tail;
                    return *this;
                } else {
                    current = current->previous;
                    return *this;
                }
            }

            ConstIterator operator--(int) {
                if (*this == list->begin()) {
                    throw std::out_of_range("operator--");
                } else if (!list->isEmpty() && current == nullptr) {
                    ConstIterator it = *this;
                    current = list->tail;
                    return it;
                } else {
                    ConstIterator it = *this;
                    current = current->previous;
                    return it;
                }
            }

            ConstIterator operator+(difference_type d) const {
                ConstIterator it = *this;
                for (difference_type i = 0; i < d; i++) {
                    it++;
                }
                return it;
            }

            ConstIterator operator-(difference_type d) const {
                ConstIterator it = *this;
                for (difference_type i = 0; i < d; i++) {
                    it--;
                }
                return it;
            }

            bool operator==(const ConstIterator& other) const {
                if (current == other.current && list == other.list) {
                    return true;
                } else {
                    return false;
                }
            }

            bool operator!=(const ConstIterator& other) const {
                if (current == other.current && list == other.list) {
                    return false;
                } else {
                    return true;
                }
            }
    };

    template<typename Type>
    class LinkedList<Type>::Iterator: public LinkedList<Type>::ConstIterator
    {
        public:
            using element_pointer = typename LinkedList::element_pointer;
            using reference = typename LinkedList::reference;

            explicit Iterator() :
                    ConstIterator() {
            }

            Iterator(const ConstIterator& other) :
                    ConstIterator(other) {
            }

            Iterator& operator++() {
                ConstIterator::operator++();
                return *this;
            }

            Iterator operator++(int) {
                auto result = *this;
                ConstIterator::operator++();
                return result;
            }

            Iterator& operator--() {
                ConstIterator::operator--();
                return *this;
            }

            Iterator operator--(int) {
                auto result = *this;
                ConstIterator::operator--();
                return result;
            }

            Iterator operator+(difference_type d) const {
                return ConstIterator::operator+(d);
            }

            Iterator operator-(difference_type d) const {
                return ConstIterator::operator-(d);
            }

            reference operator*() const {
                // ugly cast, yet reduces code duplication.
                return const_cast<reference>(ConstIterator::operator*());
            }
    };

}

#endif // AISDI_LINEAR_LINKEDLIST_H
