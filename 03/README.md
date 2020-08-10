# 03: Parser

### Task

Write a parser library for strings consisting of the following tokens:

- line
- number

The number consists of characters from 0 to 9, the string contains all other characters. Tokens are separated by spaces, tabs and first line characters.

The library user should be able to register a callback function called every time a token is found, the function receives a token. It should be possible to register your own handler for each type of token. There should also be callbacks called before the start of parsing and at the end of it.

### Usage

* ```make``` - build Parser and its tests
* ```make run ARGS="str"``` - launch Parser with string "str"
* ```make test``` - launch tests for Parser
