#include <memory>
#include <string>

#include "ast.hpp"
#include "lexer.hpp"

enum Precedence { LOWEST, SUM, PRODUCT, CALL };

static Precedence getPrecedence(TokenType type) {
  switch (type) {
    case TOK_PLUS:
    case TOK_MINUS:
      return SUM;

    case TOK_ASTERISK:
    case TOK_SLASH:
      return PRODUCT;

    default:
      return LOWEST;
  }
}

class Parser {
 private:
  std::unique_ptr<Token> curToken;
  std::unique_ptr<Token> peekToken;
  std::unique_ptr<Lexer> lexer;
  std::unique_ptr<TranslationUnitAST> TU;

  void nextToken();
  std::unique_ptr<Token> getCurToken();
  std::unique_ptr<Token> getPeekToken();
  Precedence curPrecedence();

 public:
  Parser(std::string filename);
  ~Parser(){};
  bool parse();
  bool parseTransitionUnit();
  std::unique_ptr<FunctionAST> parseFunction();
  std::unique_ptr<PrototypeAST> parsePrototype();
  std::unique_ptr<FunctionAST> parseFunctionDefinition();
  std::unique_ptr<ExprAST> parseExpression();
  std::unique_ptr<ExprAST> parsePrimary();
  std::unique_ptr<NumberAST> parseNumberExpr();
  std::unique_ptr<ExprAST> parseIdentifierExpr();
  std::unique_ptr<ExprAST> parseParenExpr();
  std::unique_ptr<CallExprAST> parseCallExpr(const std::string& callee_name);
  std::unique_ptr<ExprAST> parseBinaryOpExpr(Precedence prev_prec,
                                             std::unique_ptr<ExprAST> LHS);
};
