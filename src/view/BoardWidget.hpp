
#pragma once

#include <QWidget>
#include <QVBoxLayout>

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget* parent);
    ~BoardWidget() override = default;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    QVBoxLayout layout;

};
