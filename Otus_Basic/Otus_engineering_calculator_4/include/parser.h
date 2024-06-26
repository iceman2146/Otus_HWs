//
/*
  В данном файел описан синтаксический анализатор
  Синтаксический анализатор получает на вход поток токенов и преобразуется его в АСД.
  Методы expr(), term() и prim() реализуют логику работы алгоритма рекурсивного спуска для разбора
  арифметических выражений.
*/
#pragma once

#include <istream>

#include "astnode.h"
#include "lexer.h"

class Parser
{
public:
  explicit Parser(Lexer &lexer)
      : lexer_(lexer), tok_(Lexer::Token::undefined) {}

  Parser(const Parser &other) = delete;

  Parser &operator=(const Parser &other) = delete;

  ~Parser() = default;

  ASTNode *parse();

private:
  void next_token();

  ASTNode *expr();

  ASTNode *term();

  ASTNode *prim();

  Lexer &lexer_;
  Lexer::Token tok_;
};
