
#include <QPainter>
#include <QDebug>
#include "BoardWidget.hpp"

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent), board(this) {
    qDebug() << (board.currentLevel->playerStart);
}

void BoardWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
}
