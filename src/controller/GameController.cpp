#include "GameController.h"
#include <QDebug>

GameController::GameController(QObject *parent)
    : QObject(parent)
    , m_gameModel(new GameModel(this))
    , m_wordModel(new WordModel(this))
    , m_wordEvaluator(new WordEvaluator(this)) {
    newGame();
}

GameController::~GameController() {
    
}

void GameController::newGame() {
    m_gameModel->resetAttempts();
    m_gameModel->setGameOver(false);
    m_gameModel->setMessage("");
    
    m_correctWord = m_wordModel->getRandomWord();
    qDebug() << "New game started with word:" << m_correctWord;
    
    emit correctWordChanged();
}

void GameController::submitGuess() {
    if (m_gameModel->gameOver()) {
        return;
    }
    
    QString currentAttempt = m_gameModel->getCurrentAttempt();
    
    if (currentAttempt.length() != 5) {
        m_gameModel->setMessage("Word must be 5 letters");
        return;
    }
    
    if (!m_wordModel->isValidWord(currentAttempt)) {
        m_gameModel->setMessage("Not in word list");
        return;
    }
    
    m_gameModel->setMessage("");
    
    if (currentAttempt.toUpper() == m_correctWord) {
        m_gameModel->setGameOver(true);
        m_gameModel->setMessage("Congratulations!");
        return;
    }
    
    if (m_gameModel->currentRow() == 5) {
        m_gameModel->setGameOver(true);
        m_gameModel->setMessage("Game over! The word was " + m_correctWord);
    }
    
    m_gameModel->storeAttempt();
}

void GameController::addLetter(const QString &letter) {
    if (letter.length() != 1) {
        return;
    }
    
    m_gameModel->appendLetter(letter.at(0));
}

void GameController::deleteLetter() {
    m_gameModel->deleteLetter();
}

QString GameController::evaluateAttempt(const QString &attempt) {
    QList<int> result = m_wordEvaluator->evaluateWord(attempt.toUpper(), m_correctWord);
    QString resultStr;
    for (int code : result) {
        resultStr.append(QString::number(code));
    }
    return resultStr;
} 