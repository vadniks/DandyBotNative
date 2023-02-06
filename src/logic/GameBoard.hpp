
#pragma once

#include <QObject>
#include <QVector>
#include "../util.hpp"

class GameBoard final : public QObject {
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent, unsigned rows, unsigned columns, QVector<char>&& data);
    [[nodiscard]] const QVector<char>& objects() const;
    [[nodiscard]] char objectAt(unsigned row, unsigned column) const EXCEPT;
    void setAt(char object, unsigned row, unsigned column) EXCEPT;

    const unsigned mRows;
    const unsigned mColumns;
signals:
    void boardUpdated();
private:
    QVector<char> mObjects;
public:
    enum Objects : char {
        EMPTY = ' ',
        BLOCK = '#',
        COIN = '1',
        UNKNOWN = '\0'
    };
};
