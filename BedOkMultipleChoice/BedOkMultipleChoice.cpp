// BedOkMultipleChoice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <vector>
#include "MC.h"
#include <time.h>  
#include <Windows.h>
#include <iostream>
#include <string>


int main()
{
	questions collection_of_questions = GetQuestions();
	//PrintQuestions(collection_of_questions);
	system("pause");
	StartQuiz(collection_of_questions);
	system("pause");
	return 0;
}

void StartQuiz(questions collection_of_questions) {
	srand(time(NULL));
	system("cls");
	int right_answers = 0;
	int number_of_questions_asked = 0;
	std::vector <int> questions_asked;
	int question_number;
	while (number_of_questions_asked < collection_of_questions.number_of_questions) {
		question_number = rand() % collection_of_questions.number_of_questions;
		if (CheckIfQuestionIsAsked(questions_asked, question_number, number_of_questions_asked) == false) {
			questions_asked.push_back(question_number);
			std::cout << "Spørsmål nummer " << number_of_questions_asked + 1 << ": \n" << std::endl; 
			right_answers = AskQuestion(question_number, collection_of_questions, right_answers);
			number_of_questions_asked += 1;
			std::cout << "Antall fullførte spørsmål: " << number_of_questions_asked << "/" << collection_of_questions.number_of_questions << std::endl;
			std::cout << "Antall riktige svar: " << right_answers << std::endl;
			std::cout << "Prosent riktig: " << right_answers*100 / number_of_questions_asked << "%" <<std::endl;
			system("pause");
			system("cls");
		}
		
		
	}
	std::cout << "Testen er ferdig. Du klarte " << right_answers * 100 / number_of_questions_asked << "% av spørsmålene." << std::endl;
	//PrintQuestionsAsked(questions_asked);
}

void PrintQuestionsAsked(std::vector<int> questions_asked) {
	for (int i = 0; i < 43; i++) {
		std::cout << questions_asked[i] << ", ";
	}
}

int AskQuestion(int question_number, questions collection_of_questions, int right_answers) {
	std::cout << collection_of_questions.question_str[question_number] << std::endl;
	int answer = -1;
	for (int i = 0; i < 4; i++) {
		std::cout << collection_of_questions.answers[question_number][i] << std::endl;		
	}
	answer = GetAnswer();
	std::cout << "\n\n" << std::endl;
	if (answer == collection_of_questions.right_answer[question_number]) {
		right_answers += 1;
		std::cout << "Riktig!" << std::endl;
	}
	else {
		std::cout << "Feil! Riktig svar er: " << collection_of_questions.answers[question_number][collection_of_questions.right_answer[question_number]] << std::endl;
	}
	return right_answers;
}

int GetAnswer() {
	int answer = -1;
	bool answer_accepted = false;

	while (answer_accepted == false) {
		std::cout << "\nSkriv inn svaret her (0=a, 1=b, 2=c, 3=d): ";
		std::cin >> answer;
		if (answer > 3 || answer < 0) {
			std::cin.clear();
			std::cin.ignore(1, '\n');
			std::cout << "Ugyldig svar, prøv igjen." << std::endl;
		}
		else {
			answer_accepted = true;
		}
	}

	//system("cls");
	return answer;
}


bool CheckIfQuestionIsAsked(std::vector <int> questions_asked, int question_number, int number_of_questions_asked) {
	for (int i = 0; i < number_of_questions_asked; i++) {
		if (question_number == questions_asked[i]) {
			return true;
		}
	}
	return false;
}

void PrintQuestions(questions recvd) {
	for (int i = 0; i < recvd.number_of_questions; i++) {
		std::cout << recvd.question_str[i] << i<< std::endl;
		for (int j = 0; j < 4; j++) {
			std::cout << recvd.answers[i][j] << i << j << std::endl;
		}
		std::cout << "\n" << std::endl;
	}
}

questions GetQuestions() {
	std::string line;
	std::ifstream myfile("AllQuestions.txt");
	questions collection_of_questions;
	int i = 0;
	collection_of_questions.number_of_questions = 0;
	std::vector<std::string> temp_answers;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//std::cout << line << std::endl;
			::CharToOemA(line.c_str(), const_cast<char*>(line.c_str()));
			int index = i % 5;
			int question_number = i / 5;
			if (index == 0) {
				temp_answers.clear();
				collection_of_questions.number_of_questions += 1;
				collection_of_questions.question_str.push_back(line);
				//get the question
			}
			else if(index<4) {
				if (line[0] == '$') {
					collection_of_questions.right_answer.push_back(index - 1);
					line.erase(0, 1);
				}
				temp_answers.push_back(line);
			}
			else {
				if (line[0] == '$') {
					collection_of_questions.right_answer.push_back(index - 1);
					line.erase(0, 1);
				}
				temp_answers.push_back(line);
				collection_of_questions.answers.push_back(temp_answers);
			}
			i++;

		}
		std::cout << "All questions loaded correctly" << std::endl;
		myfile.close();
	}
	else std::cout << "Cannot open Questions.txt...";

	return collection_of_questions;
}
