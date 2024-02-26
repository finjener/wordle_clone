#ifndef WORDLEBACKEND_H
#define WORDLEBACKEND_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QQmlEngine>
#include <QSet>

class WordleBackend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentAttempt READ currentAttempt WRITE setCurrentAttempt NOTIFY currentAttemptChanged)
    Q_PROPERTY(int highlightedRow READ highlightedRow NOTIFY highlightedRowChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(bool gameOver READ isGameOver NOTIFY gameOverChanged)

public:
    explicit WordleBackend(QObject *parent = nullptr);

    Q_INVOKABLE void inputLetter(const QString &letter);
    Q_INVOKABLE void deleteLastLetter();
    Q_INVOKABLE void checkWord();
    Q_INVOKABLE bool isRowHighlighted(int rowIndex) const;
    Q_INVOKABLE bool isGameOver() const { return gameOver; }
    //    Q_INVOKABLE void restartGame();

    QString currentAttempt() const;
    void setCurrentAttempt(const QString &attempt);
    QString message() const { return m_message; }
    void setMessage(const QString& msg) {
        if (m_message != msg) {
            m_message = msg;
            emit messageChanged();
        }
    }
    void setGameOver(bool gameOver);

signals:
    void updateGrid(int row, int column, const QString &letter, const QString &color);
    void currentAttemptChanged();
    void wordMatched(int row);
    void highlightedRowChanged();
    void highlightedRowsChanged();
    void invalidWord();
    void messageChanged();
    void gameOverChanged();
    //    void gameReset();

private:
    QVector<QString> attempts;
    QString correctWord;
    int currentRow;
    int currentColumn;
    QString mCurrentAttempt;

    QString evaluateAttempt();
    void resetCurrentAttempt();
    QSet<QString> validWords;

    int m_highlightedRow = -1; // -1 means no row is highlighted
    int highlightedRow() const { return m_highlightedRow; }
    QList<int> highlightedRows;
    QString m_message;
    bool gameOver = false;
    bool m_gameOver = false;
};

#endif // WORDLEBACKEND_H
