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

#include "base_token.h"

namespace Booleval {

BaseToken::BaseToken() noexcept
    : type_(TokenType::UNKNOWN)
{}

BaseToken::BaseToken(TokenType type) noexcept
    : type_(type)
{}

bool BaseToken::operator==(BaseToken const& other) const {
    return type_  == other.type_;
}

void BaseToken::type(TokenType const type) noexcept {
    type_ = type;
}

TokenType const BaseToken::type() const noexcept {
    return type_;
}

bool const BaseToken::is(TokenType const type) const noexcept {
    return type_ == type;
}

bool const BaseToken::is_not(TokenType const type) const noexcept {
    return type_ != type;
}

bool const BaseToken::is_one_of(TokenType const type1, TokenType const type2) const noexcept {
    return is(type1) || is(type2);
}

bool const BaseToken::is_field_type() const noexcept {
    return is_one_of(TokenType::FIELD_A,
                     TokenType::FIELD_B,
                     TokenType::FIELD_C);
}

} // Booleval