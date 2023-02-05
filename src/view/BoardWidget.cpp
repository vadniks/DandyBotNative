
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) {
    setParent(parent);
}

void BoardWidget::paintEvent(QPaintEvent* event) {

    QWidget::paintEvent(event);
}
