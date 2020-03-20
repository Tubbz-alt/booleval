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

#include <gtest/gtest.h>
#include <booleval/evaluator.h>

class EvaluatorTest : public testing::Test {};

TEST_F(EvaluatorTest, DefaultConstructor) {
    booleval::evaluator evaluator;
    EXPECT_FALSE(evaluator.is_activated());
}

TEST_F(EvaluatorTest, EmptyExpression) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree(""));
    EXPECT_FALSE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({}));
}

TEST_F(EvaluatorTest, MissingClosingParenthesesExpression) {
    booleval::evaluator evaluator;
    EXPECT_FALSE(evaluator.build_expression_tree("(field_a foo or field_b bar"));
    EXPECT_FALSE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({}));
}

TEST_F(EvaluatorTest, MultipleFieldsExpression) {
    booleval::evaluator evaluator;
    EXPECT_FALSE(evaluator.build_expression_tree("field_a foo field_b"));
    EXPECT_FALSE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({}));
}

TEST_F(EvaluatorTest, EqualToOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a foo"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", "foo" }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", "bar" }
    }));
}

TEST_F(EvaluatorTest, NotEqualToOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a neq foo"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", "bar" }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", "foo" }
    }));
}

TEST_F(EvaluatorTest, GreaterThanOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a gt 1.23"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", 1.24 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", 1.22 }
    }));
}

TEST_F(EvaluatorTest, LessThanOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a lt 2"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", 1 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", 3 }
    }));
}

TEST_F(EvaluatorTest, GreaterThanOrEqualToOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a geq 1.234567"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", 1.234567 }
    }));

    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", 2.345678 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", 0.123456 }
    }));
}

TEST_F(EvaluatorTest, LessThanOrEqualToOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a leq 1.234567"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", 1.234567 }
    }));

    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", 0.123456 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", 2.345678 }
    }));
}

TEST_F(EvaluatorTest, AndOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a foo and field_b 1"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", "foo" },
        { "field_b", 1 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", "foo" },
        { "field_b", 2 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", "bar" },
        { "field_b", 1 }
    }));
}

TEST_F(EvaluatorTest, OrOperator) {
    booleval::evaluator evaluator;
    EXPECT_TRUE(evaluator.build_expression_tree("field_a foo or field_b 1"));
    EXPECT_TRUE(evaluator.is_activated());
    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", "foo" },
        { "field_b", 1 }
    }));

    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", "foo" },
        { "field_b", 2 }
    }));

    EXPECT_TRUE(evaluator.evaluate({
        { "field_a", "bar" },
        { "field_b", 1 }
    }));

    EXPECT_FALSE(evaluator.evaluate({
        { "field_a", "bar" },
        { "field_b", 2 }
    }));
}
