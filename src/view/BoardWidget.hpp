
#pragma once

#include <QWidget>
#include <QPointer>
#include "../logic/GameBoard.hpp"
#include "../logic/GameAlgorithm.hpp"

class BoardWidget final : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
    void setBoard(GameBoard* board);
    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] static QRect objectRect(unsigned row, unsigned column);
public slots:
    void onBoardChanged();
signals:
    void sizeChanged(unsigned width, unsigned height);
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QIcon iconOf(char object);

    GameAlgorithm mAlgorithm;
    GameBoard* mBoard;
    QMap<char, QIcon> mObjectDescriptions;
};
