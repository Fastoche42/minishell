/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:46:45 by fl-hote           #+#    #+#             */
/*   Updated: 2023/01/11 02:46:45 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int lex(const char* input, Token** tokens) {
	int token_count;
	char buffer[strlen(input) + 1];
	char* context;
	char* token_str;
	int inside_quote_double;
	int inside_quote_simple;
	TokenType type;
	char* env_var;
	char* value;
	Token token;

	token_count = 0;
	strcpy(buffer, input);
	context = NULL;
	token_str = strtok_r(buffer, "\"'| $", &context);
	inside_quote_double = 0;
	inside_quote_simple = 0;
	while (token_str != NULL) {
		if (*token_str == '"') {
			if(inside_quote_double)
				type = TOKEN_QUOTE_DOUBLE;
			else
				type = TOKEN_WORD;
			inside_quote_double = !inside_quote_double;
		} else if (*token_str == '\'') {
			if(inside_quote_simple)
				type = TOKEN_QUOTE_SIMPLE;
			else
				type = TOKEN_WORD;
			inside_quote_simple = !inside_quote_simple;
		} else if (*token_str == '|') {
			if(inside_quote_double || inside_quote_simple)
				type = TOKEN_WORD;
			else
				type = TOKEN_PIPE;
		} else if (*token_str == ' ') {
			if(inside_quote_double || inside_quote_simple)
				type = TOKEN_WORD;
			else
				type = TOKEN_SPACE;
		} else if (*token_str == '$') {
			env_var = strtok_r(NULL, "\"'| ", &context);
			if(env_var == NULL) {
				// Return error or throw an exception to indicate missing env var
				break;
			}
			value = getenv(env_var);
			if (value == NULL) {
				// Return error or throw an exception to indicate invalid env var
				break;
			}
			token_str = value;
			type = TOKEN_WORD;
		} else {
			type = TOKEN_WORD;
		}
		token.type = type;
		token.value = token_str;
		tokens[token_count++] = token;
		token_str = strtok_r(NULL, "\"'| $", &context);
	}

	if(inside_quote_double || inside_quote_simple)
		// Return error or throw an exception to indicate unterminated quote
	return token_count;
}

char* my_strtok_r(char* str, const char* delim, char** saveptr) {
	char* token;
	char* p;

	if (str == NULL)
		str = *saveptr;

	if (*str == '\0')
		return NULL;

	token = str;
	while(*str != '\0'){
		p = delim;
		while(*p != '\0'){
			if(*str == *p){
				*str = '\0';
				*saveptr = str + 1;
				return token;
			}
			p++;
		}
		str++;
	}
	*saveptr = NULL;
	return token;
}
