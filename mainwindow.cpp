#include "mainwindow.h"
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Добавление компонентов на форму.
    auto widget = new QWidget(parent);
    setCentralWidget(widget);
    srand(time(NULL));

    auto layout = new QGridLayout(widget);
    auto questionLabel = new QLabel("What is your question?");
    auto questionLineEdit = new QLineEdit();
    auto yesOrNoButton = new QPushButton("Yes or no");
    auto magicBallButton = new QPushButton("Magic ball");
    auto answerLabel = new QLabel();
    auto valueLabel = new QLabel();

    layout->addWidget(questionLabel, 0, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(questionLineEdit, 0, 1, 1, 1, Qt::AlignLeft);
    layout->addWidget(yesOrNoButton, 1, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(magicBallButton, 1, 1, 1, 1, Qt::AlignLeft);
    layout->addWidget(answerLabel, 2, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(valueLabel, 2, 1, 1, 1, Qt::AlignLeft);

    double a = 0.5;
    double prob[] = { 0.1, 0.15, 0.1, 0.15, 0.2, 0.05, 0.05, 0.2 };
    QString pred[] = { "Сомневаюсь", "Однозначно да", "Будущее туманно", "Не стоит",
                       "Забудь",     "Никогда",       "Вполне возможно", "Самое время!" };

    // То же самое, что и на C# OnClicked.
    connect(yesOrNoButton, &QPushButton::clicked, this, [a, answerLabel, valueLabel]() {
        double alpha = std::fmod((double)rand(), 11) / 10.;
        valueLabel->setText(QString::number(alpha));
        if (a <= alpha) {
            answerLabel->setText("Yes");
        } else {
            answerLabel->setText("No");
        }
    });

    connect(magicBallButton, &QPushButton::clicked, this, [prob, pred, answerLabel, valueLabel]() {
        double alpha = std::fmod((double)rand(), 101.) / 100.;
        valueLabel->setText(QString::number(alpha));
        for (int i = 0; i < 8; i++) {
            alpha -= prob[i];

            if (alpha <= 0.) {
                answerLabel->setText(pred[i]);
                break;
            }
        }
    });
}

MainWindow::~MainWindow()
{}
