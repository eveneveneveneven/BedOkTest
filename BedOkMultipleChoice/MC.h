#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct questions {
	std::vector<std::string> question_str;
	std::vector<std::vector<std::string>> answers;
	int number_of_questions;
	std::vector<int> right_answer;
};

void PrintQuestions(questions recvd);

questions GetQuestions();

void StartQuiz(questions collection_of_questions);
int GetAnswer();
bool CheckIfQuestionIsAsked(std::vector <int> questions_asked, int question_number, int number_of_questions_asked);
void PrintQuestionsAsked(std::vector<int> questions_asked);
int AskQuestion(int question_number, questions collection_of_questions, int right_answers);
void StartQuiz(questions collection_of_questions);