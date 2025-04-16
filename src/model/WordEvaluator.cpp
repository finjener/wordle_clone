#include "WordEvaluator.h"

WordEvaluator::WordEvaluator(QObject *parent)
    : QObject(parent) {
}

QList<int> WordEvaluator::evaluateWord(const QString &attempt, const QString &targetWord) {
    if (attempt.length() != 5 || targetWord.length() != 5) {
        return QList<int>() << 0 << 0 << 0 << 0 << 0;
    }
    
    QList<int> result;
    for (int i = 0; i < 5; ++i) {
        result.append(0);
    }
    
    QVector<bool> targetUsed(5, false);
    
    for (int i = 0; i < 5; ++i) {
        if (attempt[i] == targetWord[i]) {
            result[i] = 2;
            targetUsed[i] = true;
        }
    }
    
    for (int i = 0; i < 5; ++i) {
        if (result[i] == 2) {
            continue;
        }
        
        for (int j = 0; j < 5; ++j) {
            if (!targetUsed[j] && attempt[i] == targetWord[j]) {
                result[i] = 1;
                targetUsed[j] = true;
                break;
            }
        }
    }
    
    return result;
} 