
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
