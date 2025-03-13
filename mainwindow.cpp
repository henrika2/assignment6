/**
 * The entry point of the cat application.
 *
 * LAN QUANG HUYNH and Cheuk Yin Lau
 * 2025-2-27
 *
 * mainwindow.cpp
 *
 * This file implements the MainWindow class for the Simon game.
 * It manages the user interface (UI) components such as the start, red, and blue buttons,
 * the status label, and the progress bar. The MainWindow class connects these UI elements
 * to the game Model and applies several visual enhancements:
 *
 *  - A background gradient for the central widget.
 *  - Custom styling and hover effects for the start button.
 *  - Drop shadow effects for the buttons.
 *  - A custom styled progress bar.
 *  - Animated repositioning of the red and blue buttons with bounce easing.
 *
 * Widgets are manually positioned and repositioned on window resize events.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QWidget>
#include <QResizeEvent>
#include <QGraphicsDropShadowEffect>
#include <cmath> // for std::pow
#include <QEasingCurve>

MainWindow::MainWindow(Model* model, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(model),
    m_currentRound(0)
{
    ui->setupUi(this);

    // Set a background gradient for the central widget.
    ui->centralwidget->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f0f8ff, stop:1 #87cefa);"
        );

    // Set the initial button colors.
    ui->redButton->setStyleSheet("background-color: red;");
    ui->blueButton->setStyleSheet("background-color: blue;");
    ui->startButton->setStyleSheet(
        "QPushButton { "
        "   background-color: #3498db; "
        "   color: white; "
        "   font-weight: bold; "
        "   border: 2px solid #2980b9; "
        "   border-radius: 5px; "
        "} "
        "QPushButton:hover { "
        "   background-color: #2980b9; "
        "}"
        );
    ui->statusLabel->setStyleSheet("background-color: transparent;");
    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "   border: 2px solid #888888;"
        "   border-radius: 5px;"
        "   background-color: #E0E0E0;"
        "   text-align: center;"
        "   font: bold 12px;"
        "}"
        "QProgressBar::chunk {"
        "   border-radius: 3px;"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "                               stop:0 #6aacee, stop:1 #3498db);"
        "   margin: 1px;"
        "}"
        );

    // Add drop shadow effects to the buttons for a more dynamic look.
    QGraphicsDropShadowEffect *shadowStart = new QGraphicsDropShadowEffect(this);
    shadowStart->setBlurRadius(10);
    shadowStart->setOffset(3, 3);
    shadowStart->setColor(QColor(0, 0, 0, 150));
    ui->startButton->setGraphicsEffect(shadowStart);

    QGraphicsDropShadowEffect *shadowRed = new QGraphicsDropShadowEffect(this);
    shadowRed->setBlurRadius(10);
    shadowRed->setOffset(3, 3);
    shadowRed->setColor(QColor(0, 0, 0, 150));
    ui->redButton->setGraphicsEffect(shadowRed);

    QGraphicsDropShadowEffect *shadowBlue = new QGraphicsDropShadowEffect(this);
    shadowBlue->setBlurRadius(10);
    shadowBlue->setOffset(3, 3);
    shadowBlue->setColor(QColor(0, 0, 0, 150));
    ui->blueButton->setGraphicsEffect(shadowBlue);

    // Position widgets initially.
    positionWidgets();

    // Connect UI button clicks directly to model slots.
    connect(ui->startButton, &QPushButton::clicked, m_model, &Model::startGame);
    connect(ui->redButton, &QPushButton::clicked, [this]() { m_model->checkIsTrueButton(false); });
    connect(ui->blueButton, &QPushButton::clicked, [this]() { m_model->checkIsTrueButton(true); });

    // Connect model signals to view slots.
    connect(m_model, &Model::flashButton, this, &MainWindow::flashButton);
    connect(m_model, &Model::lose, this, &MainWindow::onLose);
    connect(m_model, &Model::totalAndCurrentRound, this, &MainWindow::updateProgressBar);
    connect(m_model, &Model::totalRoundUpdated, this, &MainWindow::totalRound);
    // When a new round starts, update the current round and animate button movement.
    connect(m_model, &Model::roundStarted, this, [this](int currentRound) {
        m_currentRound = currentRound;
        animateButtonMovement();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::totalRound(int totalRound) {
    ui->statusLabel->setText(QString("Round: %1").arg(totalRound));
    // Clear any special styling and ensure transparency.
    ui->statusLabel->setStyleSheet("background-color: transparent;");
}

void MainWindow::updateProgressBar(int current, int total) {
    ui->progressBar->setValue((total > 0) ? (current * 100 / total) : 0);
}

void MainWindow::onLose() {
    ui->statusLabel->setText("You Lose!");
    ui->statusLabel->setStyleSheet("font-size: 36px; color: red; font-weight: bold;");
}

void MainWindow::flashButton(int button, int current, int total) {
    // Compute base delay using exponential decay: 1000 * (0.9^total)
    int baseDelay = static_cast<int>(1000 * std::pow(0.9, total));
    QTimer::singleShot(baseDelay * current, this, [this, button, baseDelay]() {
        // Determine which button to flash.
        QPushButton *btn = (button == 0) ? ui->redButton : ui->blueButton;
        // Change style to simulate a flash.
        btn->setStyleSheet("background-color: yellow;");
        // Revert back after half the base delay.
        QTimer::singleShot(baseDelay / 2, this, [btn, button]() {
            if (button == 0)
                btn->setStyleSheet("background-color: red;");
            else
                btn->setStyleSheet("background-color: blue;");
        });
    });
}

///
/// positionWidgets() - Positions the Start button, Status Label, Progress Bar,
///                      Red and Blue buttons relative to the central widget.
///
void MainWindow::positionWidgets() {
    // Get the available area from the central widget.
    QRect area = ui->centralwidget->rect();
    int cx = area.width() / 2;
    int cy = area.height() / 2;

    // --- Position Start Button in the center ---
    int startW = ui->startButton->width();
    int startH = ui->startButton->height();
    int startX = cx - startW / 2;
    int startY = cy - startH / 2;
    ui->startButton->move(startX, startY);

    // --- Position Status Label above Start Button ---
    int labelW = ui->statusLabel->width();
    int labelH = ui->statusLabel->height();
    int labelX = cx - labelW / 2;
    int labelY = startY - labelH - 20; // 20 pixels above
    ui->statusLabel->move(labelX, labelY);

    // --- Position Red Button: to the left and below the Start Button ---
    int redW = ui->redButton->width();
    int redX = startX - redW - 20; // 20 pixels gap to the left
    int redY = startY + startH + 20; // aligned with progress bar vertical
    ui->redButton->move(redX, redY);

    // --- Position Blue Button: to the right of the Start Button ---
    int blueX = startX + startW + 20; // 20 pixels gap to the right
    int blueY = redY; // align vertically with red button
    ui->blueButton->move(blueX, blueY);

    // --- Position Progress Bar below both buttons ---
    int pbW = ui->progressBar->width();
    int pbX = cx - pbW / 2; // centered horizontally
    // Find the lower y-value between red and blue buttons.
    int lowerY = qMax(ui->redButton->geometry().bottom(), ui->blueButton->geometry().bottom());
    int pbY = lowerY + 20; // 20 pixels below the lower button.
    ui->progressBar->move(pbX, pbY);
}

///
/// animateButtonMovement() - Animates the Red and Blue buttons to random positions within the central widget,
///                           ensuring they do not overlap each other or the forbidden widgets (progressBar, statusLabel, startButton).
///
void MainWindow::animateButtonMovement() {
    // Get the available area from the central widget.
    QRect area = ui->centralwidget->rect();

    // Build a list of forbidden areas (widgets that should not be overlapped).
    QVector<QRect> forbidden;
    forbidden.append(ui->progressBar->geometry());
    forbidden.append(ui->statusLabel->geometry());
    forbidden.append(ui->startButton->geometry());

    // Find a new position for the Red button.
    QRect redCandidate;
    int maxAttempts = 100;
    bool redValid = false;
    for (int attempt = 0; attempt < maxAttempts && !redValid; attempt++) {
        int newX = QRandomGenerator::global()->bounded(0, area.width() - ui->redButton->width() + 1);
        int newY = QRandomGenerator::global()->bounded(0, area.height() - ui->redButton->height() + 1);
        redCandidate = QRect(newX, newY, ui->redButton->width(), ui->redButton->height());
        redValid = true;
        for (const QRect &rect : forbidden) {
            if (redCandidate.intersects(rect)) {
                redValid = false;
                break;
            }
        }
    }

    // Find a new position for the Blue button.
    QRect blueCandidate;
    bool blueValid = false;
    for (int attempt = 0; attempt < maxAttempts && !blueValid; attempt++) {
        int newX = QRandomGenerator::global()->bounded(0, area.width() - ui->blueButton->width() + 1);
        int newY = QRandomGenerator::global()->bounded(0, area.height() - ui->blueButton->height() + 1);
        blueCandidate = QRect(newX, newY, ui->blueButton->width(), ui->blueButton->height());
        blueValid = true;
        for (const QRect &rect : forbidden) {
            if (blueCandidate.intersects(rect)) {
                blueValid = false;
                break;
            }
        }
        // Ensure Blue does not overlap Red.
        if (blueValid && blueCandidate.intersects(redCandidate))
            blueValid = false;
    }

    // Animate the Red button to its new position.
    QPropertyAnimation *animRed = new QPropertyAnimation(ui->redButton, "pos");
    animRed->setDuration(1000); // 1 second duration
    animRed->setStartValue(ui->redButton->pos());
    animRed->setEndValue(redCandidate.topLeft());
    animRed->setEasingCurve(QEasingCurve::OutBounce);
    animRed->start(QAbstractAnimation::DeleteWhenStopped);

    // Animate the Blue button to its new position.
    QPropertyAnimation *animBlue = new QPropertyAnimation(ui->blueButton, "pos");
    animBlue->setDuration(1000);
    animBlue->setStartValue(ui->blueButton->pos());
    animBlue->setEndValue(blueCandidate.topLeft());
    animBlue->setEasingCurve(QEasingCurve::OutBounce);
    animBlue->start(QAbstractAnimation::DeleteWhenStopped);
}

//
// Override resizeEvent to reposition widgets when the window is resized.
//
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    positionWidgets();
}
