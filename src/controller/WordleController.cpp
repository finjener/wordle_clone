#include "WordleController.h"

WordleController::WordleController(QObject *parent)
    : QObject(parent)
    , m_wordModel(new WordModel(this))
    , m_gameModel(new GameModel(this))
    , m_wordEvaluator(new WordEvaluator(this))
    , m_targetWord("")
{
    m_wordModel->loadWordList();
    startNewGame();
    
    connect(m_gameModel, &GameModel::currentRowChanged, this, &WordleController::onCurrentRowChanged);
}

WordleController::~WordleController()
{
}

GameModel* WordleController::gameModel() const
{
    return m_gameModel;
}

void WordleController::startNewGame()
{
    m_targetWord = m_wordModel->getRandomWord();
    m_gameModel->resetAttempts();
    m_gameModel->setMessage("");
    emit targetWordChanged();
}

void WordleController::submitWord()
{
    if (m_gameModel->gameOver()) {
        return;
    }

    QString currentAttempt = m_gameModel->getCurrentAttempt();
    
    if (currentAttempt.length() != 5) {
        m_gameModel->setMessage("Word must be 5 letters!");
        return;
    }
    
    if (!m_wordModel->isValidWord(currentAttempt)) {
        m_gameModel->setMessage("Not in word list!");
        return;
    }
    
    QList<int> result = m_wordEvaluator->evaluateWord(currentAttempt, m_targetWord);
    
    for (int i = 0; i < result.size(); ++i) {
        emit letterEvaluated(m_gameModel->currentRow(), i, currentAttempt[i], result[i]);
    }

    m_gameModel->storeAttempt();
    
    if (currentAttempt == m_targetWord) {
        m_gameModel->setGameOver(true);
        m_gameModel->setMessage("Correct! Well done!");
        emit gameWon();
    } else if (m_gameModel->currentRow() >= 6) {
        m_gameModel->setGameOver(true);
        m_gameModel->setMessage("Game over! The word was: " + m_targetWord);
        emit gameLost();
    } else {
        m_gameModel->setMessage("");
    }
}

void WordleController::onCurrentRowChanged()
{
    if (m_gameModel->currentRow() > 0) {
        QString currentAttempt = m_gameModel->getCurrentAttempt();
        if (currentAttempt == m_targetWord) {
            m_gameModel->setGameOver(true);
            m_gameModel->setMessage("Correct! Well done!");
        }
    }
} 