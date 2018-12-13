#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#define RESIZING_OFFSET 1
#define RESIZING_FACTOR 2

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

    template<typename Type>
    class Vector
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
            size_type allocated_space;

            void reallocate(size_type new_space) {
                pointer old_head = head;
                head = new Type[new_space];
                allocated_space = new_space;
                for (size_type i = 0; i < size; i++) {
                    *(head + i) = *(old_head + i);
                }
                delete[] old_head;
            }

            void stretch() {
                size_type more_space;
                if (allocated_space == 0) {
                    more_space = RESIZING_OFFSET;
                } else {
                    more_space = RESIZING_FACTOR * allocated_space;
                }
                reallocate(more_space);
            }

            void insertWhenEnoughSpace(
                    const const_iterator& insertPosition,
                    const Type& item) {
                size++;
                for (iterator it = end() - 1; it != insertPosition; --it) {
                    *it = *(it - 1);
                }
                iterator insert_position_var(insertPosition);
                *insert_position_var = item;
            }

        public:
            Vector() :
                    head(nullptr), size(0), allocated_space(0) {
            }

            Vector(std::initializer_list<Type> l) {
                head = new Type[l.size()];
                allocated_space = l.size();
                int i = 0;
                typename std::initializer_list<Type>::iterator it;
                for (it = std::begin(l); it != std::end(l); ++it) {
                    *(head + (i++)) = *it;
                }
                size = l.size();
            }

            Vector(const Vector& other) :
                    Vector() {
                *this = other;
            }

            Vector(Vector&& other) :
                            head(other.head),
                            size(other.size),
                            allocated_space(other.allocated_space) {
                other.head = nullptr;
                other.size = 0;
                other.allocated_space = 0;
            }

            ~Vector() {
                delete[] head;
            }

            Vector& operator=(const Vector& other) {
                if (this != &other) {
                    delete[] head;
                    head = new Type[other.allocated_space];
                    size = other.size;
                    allocated_space = other.allocated_space;
                    for (size_type i = 0; i < size; i++) {
                        *(head + i) = *(other.head + i);
                    }
                }
                return *this;
            }

            Vector& operator=(Vector&& other) {
                if (this != &other) {
                    delete[] head;
                    head = other.head;
                    size = other.size;
                    allocated_space = other.allocated_space;
                    other.head = nullptr;
                    other.size = 0;
                    other.allocated_space = 0;
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

            void append(const Type& item) {
                if (size == allocated_space) {
                    stretch();
                }
                *(head + size) = item;
                size++;
            }

            void prepend(const Type& item) {
                if (size == allocated_space) {
                    stretch();
                }
                for (size_type i = size; i > 0; i--) {
                    *(head + i) = *(head + i - 1);
                }
                *head = item;
                size++;

            }

            void insert(
                    const const_iterator& insertPosition,
                    const Type& item) {
                if (size == allocated_space) {
                    difference_type positionOffset = 0;
                    for (iterator it = begin(); it != insertPosition; it++) {
                        positionOffset++;
                    }
                    stretch();
                    insertWhenEnoughSpace(begin() + positionOffset, item);
                } else {
                    insertWhenEnoughSpace(insertPosition, item);
                }
            }

            Type popFirst() {
                Type firstItem = *begin();
                erase(begin());
                return firstItem;
            }

            Type popLast() {
                if (isEmpty()) {
                    throw std::out_of_range("popLast");
                }
                Type lastItem = *(end() - 1);
                erase(end() - 1);
                return lastItem;
            }

            void erase(const const_iterator& position) {
                if (isEmpty() || position == end()) {
                    throw std::out_of_range("erase");
                }
                for (iterator it = position; it != end(); ++it) {
                    if (it + 1 != end()) {
                        *it = *(it + 1);
                    }
                }
                size--;
            }

            void erase(
                    const const_iterator& firstIncluded,
                    const const_iterator& lastExcluded) {
                if (isEmpty()) {
                    throw std::out_of_range("erase");
                }
                difference_type size_decrease =
                        lastExcluded.current - firstIncluded.current;
                iterator first_included_var(firstIncluded);
                for (int i = 0; lastExcluded + i != end(); i++) {
                    *(first_included_var + i) = *(lastExcluded + i);
                }
                size -= size_decrease;
            }

            iterator begin() {
                iterator it;
                it.vector = this;
                it.current = head;
                return it;
            }

            iterator end() {
                iterator it;
                it.vector = this;
                it.current = head + this->size;
                return it;
            }

            const_iterator cbegin() const {
                const_iterator it;
                it.vector = this;
                it.current = head;
                return it;
            }

            const_iterator cend() const {
                const_iterator it;
                it.vector = this;
                it.current = head + this->size;
                return it;
            }

            const_iterator begin() const {
                return cbegin();
            }

            const_iterator end() const {
                return cend();
            }
    };

    template<typename Type>
    class Vector<Type>::ConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename Vector::value_type;
            using difference_type = typename Vector::difference_type;
            using pointer = typename Vector::const_pointer;
            using reference = typename Vector::const_reference;

            pointer current;
            const Vector* vector;

            explicit ConstIterator() :
                    current(nullptr), vector(nullptr) {
            }

            reference operator*() const {
                if (*this == vector->end()) {
                    throw std::out_of_range("operator*");
                }
                return *current;
            }

            ConstIterator& operator++() {
                if (*this == vector->end()) {
                    throw std::out_of_range("operator++");
                }
                current++;
                return *this;
            }

            ConstIterator operator++(int) {
                if (*this == vector->end()) {
                    throw std::out_of_range("operator++");
                }
                ConstIterator it = *this;
                ++(*this);
                return it;
            }

            ConstIterator& operator--() {
                if (*this == vector->begin()) {
                    throw std::out_of_range("operator--");
                }
                current--;
                return *this;
            }

            ConstIterator operator--(int) {
                if (*this == vector->begin()) {
                    throw std::out_of_range("operator--");
                }
                ConstIterator it = *this;
                --(*this);
                return it;
            }

            ConstIterator operator+(difference_type d) const {
                if (current + d > vector->head + vector->size) {
                    throw std::out_of_range("operator+");
                }
                ConstIterator it = *this;
                it.current += d;
                return it;
            }

            ConstIterator operator-(difference_type d) const {
                if (current - d < vector->head) {
                    throw std::out_of_range("operator-");
                }
                ConstIterator it = *this;
                it.current -= d;
                return it;
            }

            bool operator==(const ConstIterator& other) const {
                if (current == other.current && vector == other.vector) {
                    return true;
                } else {
                    return false;
                }
            }

            bool operator!=(const ConstIterator& other) const {
                if (current == other.current && vector == other.vector) {
                    return false;
                } else {
                    return true;
                }
            }
    };

    template<typename Type>
    class Vector<Type>::Iterator: public Vector<Type>::ConstIterator
    {
        public:
            using pointer = typename Vector::pointer;
            using reference = typename Vector::reference;

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

#endif // AISDI_LINEAR_VECTOR_H
