#include "Parser.h"

const char* Parser::StateStrings[] = {
    "Начальное",
    "Объект",
    "Массив",
    "Имя",
    "После имени",
    "Перед значением",
    "Число",
    "Строка",
    "После значения",
    "Экранирование",
    "True",
    "False",
    "Null"
};



void Parser::parse(const bool autoparse) {
    if (isDone || isError) return;
    if (autoparse) {
        while ((position != jsonLength) && (jsonSource[position] != '\0')) {
            currentState->processChar(jsonSource[position]);
            if (isError)
                return;
            if (toDelete) {
                delete stateToDelete;
                toDelete = false;
            }
            position++;
        }
        if (currentState->getStateName() == StateName::Initial) {
            isDone = true;
            return;
        }
        else {
            isError = true;
            errorMessage = "unexpected end of file";
            return;
        }
    }
    else {
        if ((position == jsonLength) || (jsonSource[position] == '\0')) {
            if (currentState->getStateName() == StateName::Initial) {
                isDone = true;
                return;
            }
            else {
                isError = true;
                errorMessage = "unexpected end of file";
                return;
            }
        }
        currentState->processChar(jsonSource[position]);
        if (toDelete) {
            delete stateToDelete;
            toDelete = false;
        }
        if (!isError)
            position++;
    }
}

Parser::Parser(const char* src, const size_t length) :
    toDelete(false),
    isError(false),
    isDone(false),
    currentState((AbstractState*)(new InitialState(this))),
    stateToDelete(nullptr),
    currentNode(nullptr),
    root(nullptr),
    jsonSource(src),
    jsonLength((length) ? length : -1),
    position(0)
{}

Parser::~Parser() {
    while (!stack.empty()) {
        delete stack.back();
        stack.pop_back();
    }
    delete root;
    delete currentState;
}

const char* Parser::getState() const { return StateStrings[(unsigned int)currentState->getStateName()]; }

const std::vector<AbstractState*>* Parser::getStack() const { return &stack; }

const char* Parser::getError() const { return errorMessage.c_str(); }

bool Parser::success() const { return !isError; }

bool Parser::done() const { return isDone; }

const DataTree* Parser::getData() const { return root; }

unsigned int Parser::getPos() const { return position; }
