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

            class ConstIterator;
            class Iterator;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

        private:
            pointer head;
            size_type size;

        public:
            LinkedList() :
                    head(nullptr), size(0) {
            }

            LinkedList(std::initializer_list<value_type> l) {
                (void) l; // disables "unused argument" warning, can be removed when method is implemented.
                throw std::runtime_error("TODO");
            }

            LinkedList(const LinkedList& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            LinkedList(LinkedList&& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            ~LinkedList() {
            }

            LinkedList& operator=(const LinkedList& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            LinkedList& operator=(LinkedList&& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            bool isEmpty() const {
                throw std::runtime_error("TODO");
            }

            size_type getSize() const {
                throw std::runtime_error("TODO");
            }

            void append(const_reference item) {
                (void) item;
                throw std::runtime_error("TODO");
            }

            void prepend(const_reference item) {
                (void) item;
                throw std::runtime_error("TODO");
            }

            void insert(
                    const const_iterator& insertPosition,
                    const_reference item) {
                (void) insertPosition;
                (void) item;
                throw std::runtime_error("TODO");
            }

            value_type popFirst() {
                throw std::runtime_error("TODO");
            }

            value_type popLast() {
                throw std::runtime_error("TODO");
            }

            void erase(const const_iterator& possition) {
                (void) possition;
                throw std::runtime_error("TODO");
            }

            void erase(
                    const const_iterator& firstIncluded,
                    const const_iterator& lastExcluded) {
                (void) firstIncluded;
                (void) lastExcluded;
                throw std::runtime_error("TODO");
            }

            iterator begin() {
                throw std::runtime_error("TODO");
            }

            iterator end() {
                throw std::runtime_error("TODO");
            }

            const_iterator cbegin() const {
                throw std::runtime_error("TODO");
            }

            const_iterator cend() const {
                throw std::runtime_error("TODO");
            }

            const_iterator begin() const {
                return cbegin();
            }

            const_iterator end() const {
                return cend();
            }
    };

    template<typename Type>
    class LinkedList<Type>::ConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename LinkedList::value_type;
            using difference_type = typename LinkedList::difference_type;
            using pointer = typename LinkedList::const_pointer;
            using reference = typename LinkedList::const_reference;

            pointer current;
            const LinkedList* list;

            explicit ConstIterator() :
                    current(nullptr), list(nullptr) {
            }

            reference operator*() const {
                if (*this == list->end()) {
                    throw std::out_of_range("operator*");
                }
                return *current;
            }

            ConstIterator& operator++() {
                if (*this == list->end()) {
                    throw std::out_of_range("operator++");
                }
                current++;
                return *this;
            }

            ConstIterator operator++(int) {
                if (*this == list->end()) {
                    throw std::out_of_range("operator++");
                }
                ConstIterator it = *this;
                ++(*this);
                return it;
            }

            ConstIterator& operator--() {
                if (*this == list->begin()) {
                    throw std::out_of_range("operator--");
                }
                current--;
                return *this;
            }

            ConstIterator operator--(int) {
                if (*this == list->begin()) {
                    throw std::out_of_range("operator--");
                }
                ConstIterator it = *this;
                --(*this);
                return it;
            }

            ConstIterator operator+(difference_type d) const {
                if (current + d > list->head + list->size) {
                    throw std::out_of_range("operator+");
                }
                ConstIterator it = *this;
                it.current += d;
                return it;
            }

            ConstIterator operator-(difference_type d) const {
                if (current - d < list->head) {
                    throw std::out_of_range("operator-");
                }
                ConstIterator it = *this;
                it.current -= d;
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
            using pointer = typename LinkedList::pointer;
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
