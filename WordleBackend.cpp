#include "WordleBackend.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRandomGenerator>


WordleBackend::WordleBackend(QObject *parent)
    : QObject(parent), currentRow(0), correctWord("ADAPT") {
    // empty grid
    attempts.resize(6);

    QFile file(":/words.txt");
      if (file.open(QIODevice::ReadOnly)) {
          QTextStream stream(&file);
          while (!stream.atEnd()) {
              QString word = stream.readLine().trimmed().toUpper();
              if (!word.isEmpty()) {
                  validWords.insert(word);
              }
          }
          file.close();
      } else {
          qWarning() << "Wordlist file couldn't open!";
      }
    //answer word rechosen here
    if (!validWords.isEmpty()) {
          int randomIndex = QRandomGenerator::global()->bounded(validWords.size());
          QSet<QString>::iterator it = validWords.begin();
          std::advance(it, randomIndex);
          correctWord = *it;
      }

    resetCurrentAttempt();
    qDebug() << "Chosen wordB:" << correctWord;
}

void WordleBackend::inputLetter(const QString &letter) {
    if (currentColumn < 5) {
           mCurrentAttempt.append(letter);
           setMessage("");
           emit updateGrid(currentRow, currentColumn, letter, "grey");
           currentColumn++;
           emit currentAttemptChanged();
       }
}

void WordleBackend::deleteLastLetter() {
    if (!mCurrentAttempt.isEmpty()) {
            mCurrentAttempt.chop(1);
            currentColumn--;
            setMessage("");
            emit updateGrid(currentRow, currentColumn, "", "white");
            emit currentAttemptChanged();
        }
}

// make sure resetCurrentAttempt on currentColumn to be reset
void WordleBackend::resetCurrentAttempt() {
    mCurrentAttempt.clear();
    currentColumn = 0;
    // ... rest of your reset logic
}

void WordleBackend::checkWord() {
//    if (gameOver) {
//            setMessage("Game over. Start a new game.");
//            return;
//        }

    if (mCurrentAttempt.length() == 5) {
        QString evaluation = evaluateAttempt();
        if (!validWords.contains(mCurrentAttempt.toUpper())) {
            setMessage("Invalid word! Please delete and write valid word");
            emit invalidWord();
            return;
        }
        else{
            setMessage("");
        }

        for (int i = 0; i < 5; ++i) {
            QString color;
            // green for correct, yellow for exists, grey for absent.
            if (evaluation[i] == '2') {
                color = "green";
            } else if (evaluation[i] == '1') {
                color = "yellow";
            } else {
                color = "grey";
            }
            emit updateGrid(currentRow, i, QString(mCurrentAttempt[i]), color);
        }

        // if word exists in the word list
        if (validWords.contains(mCurrentAttempt.toUpper())) {
            if (!highlightedRows.contains(currentRow)) {
                highlightedRows.append(currentRow);
                emit highlightedRowsChanged();
            }
        }

        // Check whether the word is correct
        if (mCurrentAttempt.toUpper() == correctWord) {
            setMessage("Congrats, you won!");
            gameOver = true;
        } else if (currentRow >= 5) {//last try
            setMessage("Sorry, you lost this game. The word was " + correctWord);
            gameOver = true;
        } else {
            attempts[currentRow] = mCurrentAttempt;
            currentRow++;
            resetCurrentAttempt();
        }
    }
}

bool WordleBackend::isRowHighlighted(int rowIndex) const {
    return highlightedRows.contains(rowIndex);
}

QString WordleBackend::currentAttempt() const {
    return mCurrentAttempt;
}

void WordleBackend::setCurrentAttempt(const QString &attempt) {
    if (mCurrentAttempt == attempt)
        return;

    mCurrentAttempt = attempt;
    emit currentAttemptChanged();
}

QString WordleBackend::evaluateAttempt() {
    QString result;

    QString correctWordCopy = correctWord;

    // check correct position for letters to highlight green or yellow
    for (int i = 0; i < 5; ++i) {
        if (mCurrentAttempt[i] == correctWord[i]) {
            result += '2';
            correctWordCopy[i] = '-';
        } else {
            result += '0';
        }
    }

    // letter exist in the answer word but place is not correct so yellow
    for (int i = 0; i < 5; ++i) {
        if (result[i] == '0' && correctWordCopy.contains(mCurrentAttempt[i])) {
            result[i] = '1';
            correctWordCopy.replace(correctWordCopy.indexOf(mCurrentAttempt[i]), 1, '-');
        }
    }

    return result;
}

//void WordleBackend::restartGame() {
//    gameOver = false;
//    emit gameOverChanged();
//    currentRow = 0;
//    mCurrentAttempt.clear();
//}

void WordleBackend::setGameOver(bool gameOver) {
    if (m_gameOver != gameOver) {
        m_gameOver = gameOver;
        emit gameOverChanged();
    }
}
