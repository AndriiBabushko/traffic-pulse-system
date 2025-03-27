//
// Created by andrii on 3/27/25.
//
#pragma once

#ifndef PULSEERRORCODE_H
#define PULSEERRORCODE_H

/**
 * @enum PulseErrorCode
 * @brief Represents specific types of errors in the Pulse library.
 */
enum class PulseErrorCode {
    Unknown,
    InvalidFilePath,
    AlreadyRunning,
    NotRunning,
    ParsingError,
    DuplicateEntity
    // Add more codes as needed
};

#endif //PULSEERRORCODE_H
