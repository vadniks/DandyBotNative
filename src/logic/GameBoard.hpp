
#pragma once

#include <QObject>
#include <QVector>

class GameBoard final : public QObject {
    Q_OBJECT
public:
    explicit GameBoard(QObject* parent, unsigned rows, unsigned columns);
    [[nodiscard]] const QVector<char>& data() const;

    const unsigned mRows;
    const unsigned mColumns;
private:
    QVector<char> mData;
public:
    enum Objects : char {
        EMPTY = ' ',
        BLOCK = '#',
        COIN = '1'
    };
};
