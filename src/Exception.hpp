/*
 * Inspired by the work of Peter Sovietov's DandyBot
 * (https://github.com/true-grue/DandyBot) which was written in 2021-2022.
 *
 * Ported to the QT framework by Vad Nik
 * (https://github.com/vadniks/DandyBotNative) in 2023 for educational purpose.
 *
 * TODO: add licence
 */

#pragma once

#include <QException>
#include "util.hpp"

class Exception : public QException {
public:
    explicit Exception(QString&& what)
        : mWhat(static_cast<QString&&>(what))
    {}

    [[nodiscard]] c_str what()
    const noexcept override
    { return mWhat.toLatin1().data(); }

private:
    const QString mWhat;
};
