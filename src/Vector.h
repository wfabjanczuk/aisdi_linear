#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#define SPACE_RESIZING_OFFSET 100
#define SPACE_RESIZING_FACTOR 2

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

            // private
        public:
            pointer head = nullptr;
            size_type size = 0;
            size_type allocated_space = 0;

            void allocateSpace(size_type space) {
                pointer old_head = head;
                head = new Type[space];
                allocated_space = space;
                for (size_type i = 0; i < size; i++) {
                    *(head + i) = *(old_head + i);
                }
                delete[] old_head;
            }

            void allocateMoreSpace() {
                size_type more_space;
                if (allocated_space == 0) {
                    more_space = SPACE_RESIZING_OFFSET;
                } else {
                    more_space = SPACE_RESIZING_FACTOR * allocated_space;
                }
                allocateSpace(more_space);
            }

            void optimizeSpace() {
                size_t srf_squared;
                srf_squared = SPACE_RESIZING_FACTOR * SPACE_RESIZING_FACTOR;
                if (
                    size > SPACE_RESIZING_OFFSET
                    && size < (allocated_space / srf_squared)
                ) {
                    allocateSpace(allocated_space / SPACE_RESIZING_FACTOR);
                }
            }

        public:
            class ConstIterator;
            class Iterator;
            using iterator = Iterator;
            using const_iterator = ConstIterator;

            Vector() {
            }

            Vector(std::initializer_list<Type> l) {
                (void) l; // disables "unused argument" warning, can be removed when method is implemented.
                throw std::runtime_error("TODO");
            }

            Vector(const Vector& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            Vector(Vector&& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            ~Vector() {
            }

            Vector& operator=(const Vector& other) {
                (void) other;
                throw std::runtime_error("TODO");
            }

            Vector& operator=(Vector&& other) {
                (void) other;
                throw std::runtime_error("TODO");
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
                    allocateMoreSpace();
                }
                *(head + size) = item;
                size++;
            }

            void prepend(const Type& item) {
                (void) item;
                throw std::runtime_error("TODO");
            }

            void insert(const const_iterator& insertPosition,
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

            void erase(const const_iterator& firstIncluded,
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
