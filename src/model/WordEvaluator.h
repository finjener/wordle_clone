#ifndef WORDEVALUATOR_H
#define WORDEVALUATOR_H

#include <QObject>
#include <QList>

class WordEvaluator : public QObject
{
    Q_OBJECT

public:
    enum LetterResult {
        Incorrect = 0,
        WrongPosition = 1,
        Correct = 2
    };
    Q_ENUM(LetterResult)

    explicit WordEvaluator(QObject *parent = nullptr);

    QList<int> evaluateWord(const QString &attempt, const QString &targetWord);
};

#endif 