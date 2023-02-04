
#pragma once

#include <QWidget>
#include <QVBoxLayout>

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
    ~BoardWidget() override = default;
private:
    QVBoxLayout layout;

};
