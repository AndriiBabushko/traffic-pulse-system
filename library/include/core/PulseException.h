//
// Created by andrii on 3/27/25.
//

#pragma once

#ifndef PULSEEXCEPTION_H
#define PULSEEXCEPTION_H

#include <stdexcept>
#include <string>
#include <sstream>
#include <utility>

#include "types/PulseErrorCode.h"

/**
 * @class PulseException
 * @brief Custom exception class for the Pulse library.
 *
 * Inherits from std::runtime_error and provides additional context
 * such as error codes and optional nested exceptions.
 */
class PulseException : public std::runtime_error {
public:
    /**
     * @brief Constructs a PulseException with message, error code, and optional cause.
     * @param message The error description.
     * @param code The specific error code.
     * @param cause Optional pointer to the nested exception.
     */
    explicit PulseException(const std::string& message,
                   const PulseErrorCode code = PulseErrorCode::Unknown,
                   std::exception_ptr cause = nullptr)
        : std::runtime_error(message),
          error_code(code),
          cause(std::move(cause)) {}

    /**
     * @brief Gets the associated error code.
     * @return The PulseErrorCode.
     */
    PulseErrorCode code() const noexcept {
        return error_code;
    }

    /**
     * @brief Gets the underlying cause if available.
     * @return std::exception_ptr to the cause.
     */
    std::exception_ptr getCause() const noexcept {
        return cause;
    }

    /**
     * @brief Provides a full description of the exception, including the code.
     * @return The detailed C-style string.
     */
    const char* what() const noexcept override {
        if (cached_what.empty()) {
            std::ostringstream oss;
            oss << std::runtime_error::what();
            oss << " [Code: " << static_cast<int>(error_code) << "]";
            cached_what = oss.str();
        }
        return cached_what.c_str();
    }
private:
    PulseErrorCode error_code;
    std::exception_ptr cause;
    mutable std::string cached_what;
};

#endif // PULSEEXCEPTION_H


