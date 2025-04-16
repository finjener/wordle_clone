#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QStringList>

class GameModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList attempts READ attempts NOTIFY attemptsChanged)
    Q_PROPERTY(int currentRow READ currentRow NOTIFY currentRowChanged)
    Q_PROPERTY(int currentColumn READ currentColumn NOTIFY currentColumnChanged)
    Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)

public:
    explicit GameModel(QObject *parent = nullptr);

    QStringList attempts() const { return m_attempts; }
    int currentRow() const { return m_currentRow; }
    int currentColumn() const { return m_currentColumn; }
    bool gameOver() const { return m_gameOver; }
    QString message() const { return m_message; }

    void setGameOver(bool gameOver);
    void setMessage(const QString &message);
    void setCurrentAttempt(const QString &attempt);
    QString getCurrentAttempt() const;

    Q_INVOKABLE void appendLetter(const QChar &letter);
    Q_INVOKABLE void deleteLetter();
    Q_INVOKABLE void resetAttempts();
    Q_INVOKABLE void storeAttempt();

signals:
    void attemptsChanged();
    void currentRowChanged();
    void currentColumnChanged();
    void gameOverChanged();
    void messageChanged();

private:
    QStringList m_attempts;
    bool m_gameOver;
    int m_currentRow;
    int m_currentColumn;
    QString m_message;
};

#endif 