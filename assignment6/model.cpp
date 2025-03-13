/**
 * The entry point of the cat application.
 *
 * LAN QUANG HUYNH and Cheuk Yin Lau
 * 2025-2-27
 *
 * model.cpp
 *
 * This file implements the Model class for the Simon game.
 * The Model class manages the game state, including the current round,
 * the sequence of moves, and validating player input.
 * It emits signals to update the view with game events such as:
 *  - Total round count updates.
 *  - Flashing buttons according to the game sequence.
 *  - Player progress updates.
 *  - Initiation of a new round.
 *  - Notification when the player loses.
 *
 * All game logic is handled in this class, while the view listens to its signals
 * to update the UI accordingly.
 */

#include "model.h"
#include <cstdlib>
#include <ctime>
#include <QTimer>

Model::Model(QObject *parent)
    : QObject(parent),
    m_currentRound(0),
    m_userIndex(0)
{
    // Seed the random generator to ensure a different sequence for each game.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Model::startGame() {
    // Reset game state: round, sequence, and user progress.
    m_currentRound = 0;
    m_sequence.clear();
    m_userIndex = 0;
    // Begin the first round.
    addRound();
}

void Model::addRound() {
    // Increment the round counter.
    m_currentRound++;
    // Reset user progress for the new round.
    m_userIndex = 0;
    // Append a new random move to the sequence.
    addRandomMove();

    // Emit signals to update the view with new round information.
    emit totalRoundUpdated(m_currentRound);
    emit totalAndCurrentRound(m_userIndex, m_currentRound);
    emit roundStarted(m_currentRound);

    // Play the current sequence by emitting flash signals.
    playSequence();
}

void Model::addRandomMove() {
    // Generate a random move: 0 (Red) or 1 (Blue) and add it to the sequence.
    int move = std::rand() % 2;
    m_sequence.append(move);
}

void Model::playSequence() {
    // Iterate over the sequence and emit a flash signal for each move.
    for (int i = 0; i < m_sequence.size(); i++) {
        emit flashButton(m_sequence.at(i), i, m_currentRound);
    }
}

void Model::checkIsTrueButton(bool isBlue) {
    // Convert the boolean input to a button identifier:
    // false -> 0 (Red), true -> 1 (Blue).
    int button = isBlue ? 1 : 0;

    // Check if the user's press matches the current move in the sequence.
    if (m_userIndex < m_sequence.size() && m_sequence[m_userIndex] == button) {
        // Correct move: increment the user progress.
        m_userIndex++;
        emit totalAndCurrentRound(m_userIndex, m_currentRound);
        // If the player has completed the sequence, start a new round.
        if (m_userIndex == m_sequence.size()) {
            addRound();
        }
    } else {
        // Incorrect move: notify the view that the player lost.
        emit lose();
    }
}
