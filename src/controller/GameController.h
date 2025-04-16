#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "../model/WordModel.h"
#include "../model/GameModel.h"
#include "../model/WordEvaluator.h"

class GameController : public QObject {
    Q_OBJECT
    Q_PROPERTY(GameModel* gameModel READ gameModel CONSTANT)
    Q_PROPERTY(QString correctWord READ correctWord NOTIFY correctWordChanged)

public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController();

    GameModel* gameModel() const { return m_gameModel; }
    QString correctWord() const { return m_correctWord; }

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void submitGuess();
    Q_INVOKABLE void addLetter(const QString &letter);
    Q_INVOKABLE void deleteLetter();
    
    Q_INVOKABLE QString evaluateAttempt(const QString &attempt);

signals:
    void correctWordChanged();

private:
    GameModel* m_gameModel;
    WordModel* m_wordModel;
    WordEvaluator* m_wordEvaluator;
    QString m_correctWord;
};

#endif // GAMECONTROLLER_H 