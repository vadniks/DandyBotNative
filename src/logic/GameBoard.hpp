/*
 * Inspired by the Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
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
};
