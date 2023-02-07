
#pragma once

#include <QWidget>
#include <QPointer>
#include <QKeyEvent>
#include "../logic/GameBoard.hpp"
#include "../logic/GameAlgorithm.hpp"
#include "../Keys.hpp"

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
    void keyPressed(Keys key);
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    QIcon iconOf(char object);

    GameAlgorithm mAlgorithm;
    GameBoard* mBoard;
};
