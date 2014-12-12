#ifndef HIGHSCOREWINDOW_H
#define HIGHSCOREWINDOW_H

#include <QWidget>
#include <vector>
#include <QVBoxLayout>
#include <Qlabel>
#include <QHboxLayout>
#include <QGridLayout>
#include <QString>
#include <algorithm>
#include <list>
#include <QDebug>


class HighScoreWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HighScoreWindow(QWidget *parent = 0);

signals:

public slots:
    void updateHighScores(int n);
private:

QVBoxLayout* layout_right;
QVBoxLayout* overarching_layout;
QLabel* high_score_label;
int high_score;

int counter;

};

#endif // HIGHSCOREWINDOW_H
