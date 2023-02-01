/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:45:18 by marvin            #+#    #+#             */
/*   Updated: 2023/01/02 12:45:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Types de jetons
enum TokenType {
  TOKEN_EOF,
  TOKEN_IDENT,
  TOKEN_INTEGER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MULTIPLY,
  TOKEN_DIVIDE,
  TOKEN_LPAREN,
  TOKEN_RPAREN
};

// Structure de jeton
typedef struct Token {
  enum TokenType type;
  union {
    char *ident;
    long integer;
  } value;
} Token;

// Structure de lexer
typedef struct Lexer {
  char *input;
  size_t input_len;
  size_t pos;
  Token current_token;
} Lexer;

// Initialiser un nouveau lexer
void lexer_init(Lexer *lexer, char *input) {
  lexer->input = input;
  lexer->input_len = strlen(input);
  lexer->pos = 0;
}

// Lire le prochain caractère de l'entrée
char lexer_next_char(Lexer *lexer) {
  if (lexer->pos >= lexer->input_len) {
    return 0;
  }
  return lexer->input[lexer->pos++];
}

// Aperçu du prochain caractère de l'entrée sans le consommer
char lexer_peek_char(Lexer *lexer) {
  if (lexer->pos >= lexer->input_len) {
    return 0;
  }
  return lexer->input[lexer->pos];
}

// Passer les caractères d'espacement
void lexer_skip_whitespace(Lexer *lexer) {
  char c = lexer_peek_char(lexer);
  while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
    lexer_next_char(lexer);
    c = lexer_peek_char(lexer);
  }
}

// Lire un entier de l'entrée
long lexer_read_integer(Lexer *lexer) {
  long value = 0;
  char c = lexer_peek_char(lexer);
  while (c >= '0' && c <= '9') {
    value = value * 10 + (c - '0');
    lexer_next_char(lexer);
    c = lexer_peek_char(lexer);
  }
  return value;
}

// Lire un identificateur de l'entrée
char *lexer_read_ident(Lexer *lexer)
{
  size_t ident_len = 0;
  char c = lexer_peek_char(lexer);
  while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
  {
    ident_len++;
    lexer_next_char(lexer);
    c = lexer_peek_char(lexer);
  }

  char *ident = malloc(sizeof(char) * (ident_len + 1));
  strncpy(ident, lexer->input + lexer->pos - ident_len, ident_len);
  ident[ident_len] = 0;

  return ident;
}
