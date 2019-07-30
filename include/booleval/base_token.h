/*
 * Copyright (c) 2019, Marin Peko
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOOLEVAL_BASE_TOKEN_H
#define BOOLEVAL_BASE_TOKEN_H

#include <cstdint>

namespace Booleval {

enum class TokenType : uint8_t {
    UNKNOWN = 0,
    VALUE   = 1,

    // Logical operators
    AND = 2,
    OR  = 3,

    // Relational operators
    NEQ = 4,
    GT  = 5,
    LT  = 6,

    // Parentheses
    LP = 7,
    RP = 8,

    // Fields
    FIELD_A = 9,
    FIELD_B = 10,
    FIELD_C = 11
};

class BaseToken {
public:
    BaseToken() noexcept;
    BaseToken(TokenType type) noexcept;

    bool operator==(BaseToken const& other) const;

    virtual ~BaseToken() = default;

    void type(TokenType const type) noexcept;
    TokenType type() const noexcept;

    bool is(TokenType const type) const noexcept;
    bool is_not(TokenType const type) const noexcept;
    bool is_one_of(TokenType const type1, TokenType const type2) const noexcept;

    template <typename... Types>
    bool is_one_of(TokenType const type1, TokenType const type2, Types const ... types) const noexcept;

    bool is_field_type() const noexcept;

private:
    TokenType type_;
};

template <typename... Types>
bool BaseToken::is_one_of(TokenType const type1, TokenType const type2, Types const ... types) const noexcept {
    return is(type1) || is_one_of(type2, types...);
}

} // Booleval

#endif // BOOLEVAL_BASE_TOKEN_H