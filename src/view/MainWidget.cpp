
#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent), mLayout(this), mBoardWidget(this), mInfoWidget(nullptr, mBoardWidget.algorithm())
{
    mLayout.addWidget(&mBoardWidget, 0, Qt::AlignLeft);
    mLayout.addWidget(&mInfoWidget, 0, Qt::AlignRight);
    mLayout.setContentsMargins(0, 0, 0, 0);
    connect(&mBoardWidget, &BoardWidget::sizeChanged, this, &MainWidget::onBoardSizeChanged);
}

QSize MainWidget::sizeHint() const {
    return QWidget::sizeHint();
//    const auto a = mBoardWidget.size();//mLayout.totalSizeHint();
//    const auto boardSize = a; //mBoardWidget.sizeHint(), infoSize = mInfoWidget.sizeHint();
//    return {boardSize.width() - 18 /*+ infoSize.width()*/, boardSize.height() - 18 /*>= mInfoWidget.height() ? boardSize.height() : boardSize.height() + mInfoWidget.height()*/};
}

void MainWidget::onBoardSizeChanged(unsigned int width, unsigned int height) {
//    const auto size = mInfoWidget.sizeHint();
//    const auto newWidth = static_cast<signed>(width)/* + size.width()*/,
//        newHeight = static_cast<signed>(height)/* + size.height()*/;
//
//    setFixedSize(newWidth, newHeight);
    const auto size = sizeHint();
    emit sizeChanged(size.width(), size.height());
//    emit sizeChanged(newWidth, newHeight);
}