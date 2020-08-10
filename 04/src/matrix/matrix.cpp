#include "matrix.h"

#include <sstream>
#include <stdexcept>
#include <utility>

Matrix::Row::Row(std::initializer_list<int> init)
    : row_(std::move(init))
{
}

std::vector<int>::iterator Matrix::Row::begin() {
    return row_.begin();
}

std::vector<int>::iterator Matrix::Row::end() {
    return row_.end();
}

std::vector<int>::const_iterator Matrix::Row::begin() const {
    return row_.cbegin();
}

std::vector<int>::const_iterator Matrix::Row::end() const {
    return row_.cend();
}

size_t Matrix::Row::size() const {
    return row_.size();
}

int& Matrix::Row::operator [](const size_t id) {
    return row_.at(id);
}

int Matrix::Row::operator [](const size_t id) const {
    return row_.at(id);
}

Matrix::Matrix(const std::vector<Matrix::Row>& matrix)
    : matrix_(matrix)
{
}

Matrix::Matrix(std::vector<Matrix::Row>&& matrix)
    : matrix_(std::move(matrix))
{
}

Matrix::Matrix(std::initializer_list<Row> init)
    : matrix_(std::move(init))
{
}

std::vector<Matrix::Row>::iterator Matrix::begin() {
    return matrix_.begin();
}

std::vector<Matrix::Row>::iterator Matrix::end() {
    return matrix_.end();
}

size_t Matrix::getRowsSize() const {
    return matrix_.size();
}

size_t Matrix::getColumnsSize() const {
    return matrix_.empty() ? 0 : matrix_[0].size();
}

Matrix::Row& Matrix::operator [](const size_t id) {
    return matrix_.at(id);
}

const Matrix::Row& Matrix::operator [](const size_t id) const {
    return matrix_.at(id);
}

Matrix& Matrix::operator *= (const int value) {
    for (auto& row : matrix_) {
        for (auto& item : row) {
            item *= value;
        }
    }
    return *this;
}
