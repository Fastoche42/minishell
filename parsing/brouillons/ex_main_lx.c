#include "lexer.c"

int main(int argc, char **argv)
{
  Lexer lexer;
  lexer_init(&lexer, "2 + 3 * 4");

  while (1) {
	Token token = lexer_get_next_token(&lexer);

	if (token.type == TOKEN_EOF) {
	  break;
	}

	if (token.type == TOKEN_INTEGER) {
	  printf("TOKEN_INTEGER: %ld\n", token.value.integer);
	} else if (token.type == TOKEN_IDENT) {
	  printf("TOKEN_IDENT: %s\n", token.value.ident);
	  free(token.value.ident);
	} else {
	  printf("TOKEN_%s\n", token_type_name(token.type));
	}
  }

  return 0;
}
