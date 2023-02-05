
#include <QPainter>
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) :
    QWidget(parent),
    board(GameBoard(this))
{  }

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
}
