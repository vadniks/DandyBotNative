
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "BoardWidget.hpp"
#include "InfoWidget.hpp"

class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent);
public slots:
    void onBoardSizeChanged(unsigned width, unsigned height);
signals:
    void sizeChanged(unsigned width, unsigned height);
private:
    QHBoxLayout mLayout;
    BoardWidget mBoardWidget;
    InfoWidget mInfoWidget;
};
