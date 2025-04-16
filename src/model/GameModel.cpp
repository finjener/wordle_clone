#include "GameModel.h"

GameModel::GameModel(QObject *parent)
    : QObject(parent)
    , m_gameOver(false)
    , m_currentRow(0)
    , m_currentColumn(0)
    , m_message("") {
    
    resetAttempts();
}

void GameModel::setGameOver(bool gameOver) {
    if (m_gameOver != gameOver) {
        m_gameOver = gameOver;
        emit gameOverChanged();
    }
}

void GameModel::setMessage(const QString &message) {
    if (m_message != message) {
        m_message = message;
        emit messageChanged();
    }
}

void GameModel::setCurrentAttempt(const QString &attempt) {
    if (m_currentRow < m_attempts.size()) {
        m_attempts[m_currentRow] = attempt;
        m_currentColumn = attempt.length();
        emit attemptsChanged();
    }
}

QString GameModel::getCurrentAttempt() const {
    if (m_currentRow < m_attempts.size()) {
        return m_attempts[m_currentRow];
    }
    return "";
}

void GameModel::appendLetter(const QChar &letter) {
    if (m_gameOver) return;
    
    if (m_currentRow < m_attempts.size() && m_currentColumn < 5) {
        QString attempt = m_attempts[m_currentRow];
        attempt.append(letter);
        m_attempts[m_currentRow] = attempt;
        m_currentColumn++;
        
        emit attemptsChanged();
        emit currentColumnChanged();
    }
}

void GameModel::deleteLetter() {
    if (m_gameOver) return;
    
    if (m_currentRow < m_attempts.size() && m_currentColumn > 0) {
        QString attempt = m_attempts[m_currentRow];
        attempt.chop(1);
        m_attempts[m_currentRow] = attempt;
        m_currentColumn--;
        
        emit attemptsChanged();
        emit currentColumnChanged();
    }
}

void GameModel::resetAttempts() {
    m_attempts.clear();
    for (int i = 0; i < 6; ++i) {
        m_attempts.append("");
    }
    
    m_currentRow = 0;
    m_currentColumn = 0;
    m_gameOver = false;
    
    emit attemptsChanged();
    emit currentRowChanged();
    emit currentColumnChanged();
    emit gameOverChanged();
}

void GameModel::storeAttempt() {
    if (m_gameOver) return;
    
    if (m_currentRow < 6) {
        m_currentRow++;
        m_currentColumn = 0;
        
        emit currentRowChanged();
        emit currentColumnChanged();
    }
} 