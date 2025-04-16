#include "WordModel.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

WordModel::WordModel(QObject *parent)
    : QObject(parent) {
    loadWordList();
}

void WordModel::loadWordList() {
    m_wordList.clear();
    m_validGuesses.clear();
    
    QStringList possiblePaths;
    possiblePaths << "WORDS"
                  << QDir::currentPath() + "/WORDS"
                  << QCoreApplication::applicationDirPath() + "/WORDS"
                  << "../WORDS"
                  << "../../WORDS";
    
    bool fileLoaded = false;
    
    for (const QString &path : possiblePaths) {
        QFile wordFile(path);
        if (wordFile.exists() && wordFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&wordFile);
            while (!in.atEnd()) {
                QString word = in.readLine().trimmed().toUpper();
                if (word.length() == 5) {
                    m_wordList.append(word);
                    m_validGuesses.insert(word);
                }
            }
            wordFile.close();
            
            qDebug() << "Loaded" << m_wordList.size() << "words from" << path;
            qDebug() << "Valid guesses dictionary has" << m_validGuesses.size() << "words";
            
            fileLoaded = true;
            break;
        }
    }
    
    if (!fileLoaded) {
        qWarning() << "Failed to open WORDS file from any of these paths:" << possiblePaths;
        
        QStringList fallbackWords = {"HELLO", "WORLD", "APPLE", "GRAPE", "BROWN", "CLOUD", "DREAM"};
        for (const QString &word : fallbackWords) {
            m_wordList.append(word);
            m_validGuesses.insert(word);
        }
        qDebug() << "Using fallback word list with" << m_wordList.size() << "words";
    }
}

QString WordModel::getRandomWord() const {
    if (m_wordList.isEmpty()) {
        return "HELLO";
    }
    
    int randomIndex = QRandomGenerator::global()->bounded(m_wordList.size());
    return m_wordList[randomIndex];
}

bool WordModel::isValidWord(const QString &word) const {
    QString upperWord = word.toUpper();
    return m_validGuesses.contains(upperWord);
} 