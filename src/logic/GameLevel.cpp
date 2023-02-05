
#include "GameLevel.hpp"
#include "Block.hpp"
#include "Coin.hpp"

GameLevel::GameLevel(
    QObject* parent,
    unsigned id,
    Position&& playerStart,
    unsigned scoreToProceed,
    const QString& map
) :
    QObject(parent),
    id(id),
    playerStart(playerStart),
    scoreToProceed(scoreToProceed)
{
    using Row = QVector<const QObject*>;

    const char16_t hash = QChar('#').unicode();
    const char16_t one = QChar('1').unicode();
    const char16_t newLine = QChar('\n').unicode();

    auto row = new Row();
    for (const QChar& qChar : map) { switch (qChar.unicode()) {
        case hash:
            row->push_back(new Block(this));
            break;
        case one:
            row->push_back(new Coin(this, 1));
            break;
        case newLine:
            matrix.push_back(row);
            row = new Row();
            break;
        default:
            row->push_back(nullptr);
            break;
    } }
}

GameLevel::~GameLevel() {
    for (QVector<const QObject*>* row : matrix) {
        for (const QObject* object : *row)
            delete object;
        delete row;
    }
}
