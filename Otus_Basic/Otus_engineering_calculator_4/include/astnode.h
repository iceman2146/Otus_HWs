// OTUS C++ basic course homework.
// ASTNode
/*
  В данном файле описано абстрактное синтаксическое дерево (АСД) 
  AST - это внутреннее представление программы внутри компилятора.
*/
#pragma once

#include <cctype>
#include <iostream>
#include <string>

class ASTNode
{
public:
  explicit ASTNode(const std::string &repr);

  ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);

  ASTNode(const ASTNode &other) = delete;

  ASTNode &operator=(const ASTNode &other) = delete;

  ~ASTNode();

  std::string repr() const { return repr_; }

  void print(std::ostream &out) const;

private:
  void inner_print(std::ostream &out, size_t indent) const;

  std::string repr_;
  ASTNode *lhs_;
  ASTNode *rhs_;
};
