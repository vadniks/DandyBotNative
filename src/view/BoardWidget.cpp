
#include <QPainter>
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent) {  }

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
}
