
#pragma once

#include <QException>
#include "util.hpp"

class Exception : public QException {
public:
    explicit Exception(const QString&& what) : mWhat(what) {}
    [[nodiscard]] const char* what() const noexcept override { return mWhat.toLatin1().data(); }
private:
    const QString mWhat;
};
