#pragma once

#include <vector>

class Matrix {
public :
    struct Row {
    private :
        std::vector<int> row_;

    public :
        Row() = default;
        Row(const Row&) = default;
        Row(Row&&) = default;

        Row(std::initializer_list<int> init);

        std::vector<int>::iterator begin();
        std::vector<int>::iterator end();

        std::vector<int>::const_iterator begin() const;
        std::vector<int>::const_iterator end() const;

        size_t size() const;

        int& operator [](const size_t id);
        int operator [](const size_t id) const;
    };

    std::vector<Row> matrix_;

public :
    Matrix() = default;
    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) = default;

    Matrix(const std::vector<Row>& matrix);
    Matrix(std::vector<Row>&& matrix);

    Matrix(std::initializer_list<Row> init);

    std::vector<Row>::iterator begin();
    std::vector<Row>::iterator end();

    size_t getRowsSize() const;
    size_t getColumnsSize() const;

    Row& operator [](const size_t id);
    const Row& operator [](const size_t id) const;

    Matrix& operator *= (const int value);
};
