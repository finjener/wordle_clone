#ifndef WORDLECONTROLLER_H
#define WORDLECONTROLLER_H

#include <QObject>
#include "../model/WordModel.h"
#include "../model/GameModel.h"
#include "../model/WordEvaluator.h"

class WordleController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameModel* gameModel READ gameModel CONSTANT)
    Q_PROPERTY(QString targetWord READ targetWord NOTIFY targetWordChanged)

public:
    explicit WordleController(QObject *parent = nullptr);
    ~WordleController();

    GameModel* gameModel() const;
    QString targetWord() const { return m_targetWord; }

    Q_INVOKABLE void startNewGame();
    Q_INVOKABLE void submitWord();

signals:
    void targetWordChanged();
    void letterEvaluated(int row, int column, QChar letter, int result);
    void gameWon();
    void gameLost();

private slots:
    void onCurrentRowChanged();

private:
    WordModel* m_wordModel;
    GameModel* m_gameModel;
    WordEvaluator* m_wordEvaluator;
    QString m_targetWord;
};

#endif 