
#pragma once

#include <QObject>
#include <QVector>
#include <functional>
#include "../util.hpp"

class GameBoard final : public QObject {
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent, unsigned rows, unsigned columns, QVector<char>&& objects) EXCEPT;
    [[nodiscard]] const QVector<char>& objects() const;
    [[nodiscard]] char objectAt(unsigned row, unsigned column) const EXCEPT;
    void setAt(char object, unsigned row, unsigned column) EXCEPT;
    void move(unsigned fromRow, unsigned fromColumn, unsigned toRow, unsigned toColumn) EXCEPT;
    [[nodiscard]] unsigned rows() const;
    [[nodiscard]] unsigned columns() const;
    void setSize(unsigned rows, unsigned columns) EXCEPT;
signals:
    void boardUpdated();
private:
    unsigned mRows;
    unsigned mColumns;
    QVector<char> mObjects;
public:
    enum Objects : char {
        EMPTY = ' ',
        BLOCK = '#',
        COIN = '1',
        UNKNOWN = '\0'
    };
};
