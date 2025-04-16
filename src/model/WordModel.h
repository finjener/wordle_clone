#ifndef WORDMODEL_H
#define WORDMODEL_H

#include <QObject>
#include <QStringList>
#include <QSet>
#include <QRandomGenerator>

class WordModel : public QObject {
    Q_OBJECT

public:
    explicit WordModel(QObject *parent = nullptr);
    
    void loadWordList();
    
    QString getRandomWord() const;
    
    bool isValidWord(const QString &word) const;
    
    int wordCount() const { return m_wordList.size(); }

private:
    QStringList m_wordList;
    QSet<QString> m_validGuesses;
};

#endif // WORDMODEL_H 