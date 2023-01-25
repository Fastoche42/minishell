enum TokenType {
	TOKEN_LS,
	TOKEN_CD,
	TOKEN_PATH,
	TOKEN_OPTION,
	TOKEN_STRING,
	TOKEN_EOF
};

struct Token {
	enum TokenType type;
	char *value;
};

struct Tokenizer {
	char *input;
	int position;
};

struct Tokenizer *tokenizer_new(char *input) {
	struct Tokenizer *tokenizer = malloc(sizeof(struct Tokenizer));
	tokenizer->input = input;
	tokenizer->position = 0;
	return tokenizer;
}

struct Token *tokenizer_next(struct Tokenizer *tokenizer) {
	if (tokenizer->position >= strlen(tokenizer->input)) {
		return (struct Token){ TOKEN_EOF, "" };
	}
	char current = tokenizer->input[tokenizer->position];
	if (current == ' ') {
		tokenizer->position++;
		return tokenizer_next(tokenizer);
	}
	if (current == 'l' && tokenizer->input[tokenizer->position + 1] == 's') {
		tokenizer->position += 2;
		return (struct Token){ TOKEN_LS, "ls" };
	} else if (current == 'c' && tokenizer->input[tokenizer->position + 1] == 'd') {
		tokenizer->position += 2;
		return (struct Token){ TOKEN_CD, "cd" };
	} else if (current == '/') {
		int start = ++tokenizer->position;
=====
	} else if (current == '/') {
		int start = ++tokenizer->position;
		while (tokenizer->input[tokenizer->position] != ' ' && tokenizer->input[tokenizer->position] != '\0') {
			tokenizer->position++;
		}
		int length = tokenizer->position - start;
		char *value = calloc(length + 1, sizeof(char));
		strncpy(value, tokenizer->input + start, length);
		return (struct Token){ TOKEN_PATH, value };
	} else if (current == '-' || current == '+') {
		int start = tokenizer->position++;
		while (tokenizer->input[tokenizer->position] != ' ' && tokenizer->input[tokenizer->position] != '\0') {
			tokenizer->position++;
		}
		int length = tokenizer->position - start;
		char *value = calloc(length + 1, sizeof(char));
		strncpy(value, tokenizer->input + start, length);
		return (struct Token){ TOKEN_OPTION, value };
	} else if (current == '\"' || current == '\'') {
		char end = current;
		int start = ++tokenizer->position;
		while (tokenizer->input[tokenizer->position] != end) {
			tokenizer->position++;
		}
		int length = tokenizer->position - start;
		char *value = calloc(length + 1, sizeof(char));
		strncpy(value, tokenizer->input + start, length);
		tokenizer->position++;
		return (struct Token){ TOKEN_STRING, value };
	} else {
		tokenizer->position++;
		return tokenizer_next(tokenizer);
	}
}
