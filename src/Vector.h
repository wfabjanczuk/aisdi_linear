#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#define RESIZING_OFFSET 100
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

        private:
            pointer head;
            size_type size;
            size_type allocated_space;

            size_type calculateRequiredSpace(size_type content_size) {
                size_type required_space = RESIZING_OFFSET;
                if (content_size < RESIZING_OFFSET) {
                    return required_space;
                } else {
                    do {
                        required_space *= RESIZING_FACTOR;
                    } while (content_size < required_space);
                    return required_space;
                }
            }

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

        public:
            class ConstIterator;
            class Iterator;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

            Vector() :
                    head(nullptr), size(0), allocated_space(0) {
            }

            Vector(std::initializer_list<Type> l) {
                size_type required_space;
                required_space = calculateRequiredSpace(l.size());
                head = new Type[required_space];
                allocated_space = required_space;
                int i = 0;
                typename std::initializer_list<Type>::iterator it;
                for (it = std::begin(l); it != std::end(l); ++it) {
                    *(head + (i++)) = *it;
                }
                size = l.size();
            }

            Vector(const Vector& other) {
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
                    head = other.head;
                    size = other.size;
                    allocated_space = other.allocated_space;
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
                (void) insertPosition;
                (void) item;
                throw std::runtime_error("TODO");
            }

            Type popFirst() {
                throw std::runtime_error("TODO");
            }

            Type popLast() {
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
    class Vector<Type>::ConstIterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = typename Vector::value_type;
            using difference_type = typename Vector::difference_type;
            using pointer = typename Vector::const_pointer;
            using reference = typename Vector::const_reference;

            explicit ConstIterator() {
            }

            reference operator*() const {
                throw std::runtime_error("TODO");
            }

            ConstIterator& operator++() {
                throw std::runtime_error("TODO");
            }

            ConstIterator operator++(int) {
                throw std::runtime_error("TODO");
            }

            ConstIterator& operator--() {
                throw std::runtime_error("TODO");
            }

            ConstIterator operator--(int) {
                throw std::runtime_error("TODO");
            }

            ConstIterator operator+(difference_type d) const {
                (void) d;
                throw std::runtime_error("TODO");
            }

            ConstIterator operator-(difference_type d) const {
                (void) d;
                throw std::runtime_error("TODO");
            }

            bool operator==(const ConstIterator& other) const {
                (void) other;
                throw std::runtime_error("TODO");
            }

            bool operator!=(const ConstIterator& other) const {
                (void) other;
                throw std::runtime_error("TODO");
            }
    };

    template<typename Type>
    class Vector<Type>::Iterator: public Vector<Type>::ConstIterator
    {
        public:
            using pointer = typename Vector::pointer;
            using reference = typename Vector::reference;

            explicit Iterator() {
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
