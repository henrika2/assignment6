/**
 * The entry point of the cat application.
 *
 * LAN QUANG HUYNH and Cheuk Yin Lau
 * 2025-2-27
 *
 * model.h
 *
 * This file declares the Model class for the Simon game.
 * The Model class is responsible for managing the game state, including
 * the current round, the sequence of moves, and validating player input.
 * It emits signals to update the view with game events such as:
 *  - Total round count updates.
 *  - Flashing buttons for the sequence.
 *  - Player progress in the current round.
 *  - When a new round starts.
 *  - When the player loses.
 *
 * Usage:
 *  - Construct the Model as a QObject.
 *  - The view (e.g., MainWindow) connects to the Model's signals to update the UI.
 */

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>

class Model : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new Model object.
     * @param parent Optional parent QObject.
     */
    explicit Model(QObject *parent = nullptr);

    /**
     * @brief Returns the current round number.
     * @return The current round.
     */
    int currentRound() const { return m_currentRound; }

    /**
     * @brief Returns the sequence of moves.
     * @return A QVector<int> containing the sequence (0 for Red, 1 for Blue).
     */
    QVector<int> sequence() const { return m_sequence; }

public slots:
    /**
     * @brief Starts the game by resetting the state and beginning the first round.
     */
    void startGame();

    /**
     * @brief Adds a new round, updates the sequence, and emits signals for the view.
     */
    void addRound();

    /**
     * @brief Checks if the player's button press is correct.
     * @param isBlue True if the blue button is pressed, false if the red button is pressed.
     */
    void checkIsTrueButton(bool isBlue);

signals:
    /**
     * @brief Emitted when the player makes an incorrect move.
     */
    void lose();

    /**
     * @brief Emitted to update the view with the total round count.
     * @param totalRounds The total number of rounds.
     */
    void totalRoundUpdated(int totalRounds);

    /**
     * @brief Emitted to notify the view that a button should flash.
     * @param button Identifier of the button (0 for Red, 1 for Blue).
     * @param current The current index in the sequence being flashed.
     * @param total The total number of moves in the sequence.
     */
    void flashButton(int button, int current, int total);

    /**
     * @brief Emitted to update the view with the player's current progress.
     * @param current The number of moves the player has correctly matched.
     * @param total The total number of moves in the current round.
     */
    void totalAndCurrentRound(int current, int total);

    /**
     * @brief Emitted when a new round starts.
     * @param currentRound The current round number.
     */
    void roundStarted(int currentRound);

private:
    int m_currentRound;     ///< The current round number.
    QVector<int> m_sequence;    ///< The sequence of moves (0 for Red, 1 for Blue).
    int m_userIndex;        ///< The index of the next move the player needs to match.

    /**
     * @brief Adds a random move (0 or 1) to the sequence.
     */
    void addRandomMove();

    /**
     * @brief Plays the sequence by iterating over m_sequence and emitting flashButton signals.
     */
    void playSequence();
};

#endif // MODEL_H
