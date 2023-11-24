#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream> 
#include <vector>
#include <stack>
#include <deque>
#include <list>
#include<algorithm>
#include<set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

list<string> Files; //All File Names
list < pair<string, string>>L;
list<string>Passwords;
struct state {
	list<list<char>> text;
	list<list<char>>::iterator row_iterator;
	list<char>::iterator col_iterator;
	int row, col;
};
class CurrentFile {
	//string password;
	int CountSpecialCharacters(){
		int specialCharCount = 0;
		for (auto row = text.begin(); row != text.end(); row++) {
			for (auto col = (*row).begin(); col != (*row).end(); col++) {
				if (!isalnum(*col) && !isspace(*col))
					specialCharCount++;
			}
		}
		return specialCharCount;
	}
	
	int CountWords() {
		int wordCount = 0;
		bool inWord = false;
		for (auto row = text.begin(); row != text.end(); row++) {
			for (auto col = (*row).begin(); col != (*row).end(); col++) {
				if (isalnum(*col)) {
					if (!inWord) {
						inWord = true;
						wordCount++;
					}
				}
				else
					inWord = false;
			}
		}
		return wordCount;
	}
	
	long long FindLargestWordLength() {
		long long largestWordLength = 0;
		for (auto row = text.begin(); row != text.end(); ++row) {
			auto col = (*row).begin();
			while (col != (*row).end()) {
				while (col != (*row).end() && isspace(*col))
					++col;
				int currentWordLength = 0;
				while (col != (*row).end() && isalnum(*col)) {
					++col;
					++currentWordLength;
				}
				if (currentWordLength > largestWordLength) {
					largestWordLength = currentWordLength;
				}
				while (col != (*row).end() && !isalnum(*col))
					++col;
			}
		}
		return largestWordLength;
	}

	long long FindSmallestWordLength() {
		long long smallestWordLength = LLONG_MAX;

		for (auto row = text.begin(); row != text.end(); ++row) {
			auto col = (*row).begin();
			while (col != (*row).end()) {
				while (col != (*row).end() && isspace(*col))
					++col;
				int currentWordLength = 0;
				while (col != (*row).end() && isalnum(*col)) {
					++col;
					++currentWordLength;
				}
				if (currentWordLength > 0 && currentWordLength < smallestWordLength)
					smallestWordLength = currentWordLength;
				while (col != (*row).end() && !isalnum(*col))
					++col;
			}
		}
		return (smallestWordLength == LLONG_MAX) ? 0 : smallestWordLength;
	}

	int CountSentences() {
		int sentenceCount = 0;
		for (auto row = text.begin(); row != text.end(); ++row) {
			for (auto col = (*row).begin(); col != (*row).end(); ++col) {
				if (*col == '.' || *col == '?' || *col == '!') {
					auto nextCol = col;
					++nextCol;
					if (nextCol == (*row).end() || isspace(*nextCol))
						++sentenceCount;
				}
			}
		}
		return sentenceCount;
	}

	int CountSubstring(const string& substring) {
		int count = 0;
		for (auto row = text.begin(); row != text.end(); ++row) {
			for (auto col = (*row).begin(); col != (*row).end(); ++col) {
				auto it = col;
				auto substringIt = substring.begin();
				while (it != (*row).end() && substringIt != substring.end() && *it == *substringIt) {
					++it;
					++substringIt;
				}
				if (substringIt == substring.end())
					++count;
			}
		}
		return count;
	}

	int AvgWordLength() {
		int word_length = 0;
		for (auto row = text.begin(); row != text.end(); ++row) {
			auto col = (*row).begin();
			while (col != (*row).end()) {
				while (col != (*row).end() && isspace(*col))
					++col;
				double currentWordLength = 0;
				while (col != (*row).end() && isalnum(*col)) {
					++col;
					++word_length;
				}
				while (col != (*row).end() && !isalnum(*col))
					++col;
			}
		}
		return word_length;
	}
	
	int CountParagraphs() {
		int paragraphCount = 0;
		bool inParagraph = false;
		for (auto row = text.begin(); row != text.end(); ++row) {
			if ((*row).empty()) {
				if (inParagraph) {
					paragraphCount++;
					inParagraph = false;
				}
				else
					inParagraph = true;
			}
			else
				inParagraph = false;
		}
		return paragraphCount;
	}
	void PrintParagraphC() {
		int paragraphs = CountParagraphs();

		gotoRowCol(33, 0);
		cout << "Number of Paragraphs: " << paragraphs;
	}

	string FindSmallestWord() {
		string smallestWord;
		size_t smallestLength = SIZE_MAX;
		for (auto row = text.begin(); row != text.end(); ++row) {
			auto col = (*row).begin();
			while (col != (*row).end()) {
				while (col != (*row).end() && isspace(*col))
					++col;
				size_t currentWordLength = 0;
				auto start = col;
				while (col != (*row).end() && isalnum(*col)) {
					++col;
					++currentWordLength;
				}
				if (currentWordLength > 0 && currentWordLength < smallestLength) {
					smallestLength = currentWordLength;
					smallestWord.assign(start, col);
				}
				while (col != (*row).end() && !isalnum(*col))
					++col;
			}
		}
		return smallestWord;
	}

	string FindLargestWord() {
		long long largestWordLength = 0;
		string largestWord;
		for (auto row = text.begin(); row != text.end(); ++row) {
			auto col = (*row).begin();
			while (col != (*row).end()) {
				while (col != (*row).end() && isspace(*col))
					++col;
				int currentWordLength = 0;
				auto start = col;
				while (col != (*row).end() && isalnum(*col)) {
					++col;
					++currentWordLength;
				}
				if (currentWordLength > largestWordLength) {
					largestWordLength = currentWordLength;
					largestWord = string(start, col);
				}
				while (col != (*row).end() && !isalnum(*col))
					++col;
			}
		}
		return largestWord;
	}

	void PrintSpecialCharacterCount(){
		int specialCharCount = CountSpecialCharacters();
		gotoRowCol(5, 140);
		cout << "Special Characters: " << specialCharCount;
	}
	void PrintWordsCount() {
		double words = CountWords();
		gotoRowCol(10, 140);
		cout << "Words count : " << words;
	}
	void PrintAvgWordLength() {
		int length = AvgWordLength();
		int count = CountWords();
		double avg = length / count;
		gotoRowCol(15, 140);
		cout << "Avg Word length : " << avg;
	}
	void PrintLargestWordLength() {
		long long length = FindLargestWordLength();
		gotoRowCol(20, 140);
		cout << "Largest Word length : " << length;
	}
	void PrintSmallestWordLength() {
		long long length = FindSmallestWordLength();
		gotoRowCol(25, 140);
		cout << "Smallest Word length : " << length;
	}
	void PrintSentenceCount() {
		int sentences = CountSentences();

		gotoRowCol(30, 140);
		cout << "Number of Sentences: " << sentences;
	}
	void PrintSmallestWord() {
		string smallestWord = FindSmallestWord();
		gotoRowCol(37, 0);
		cout << "Smallest Word: " << smallestWord;
	}
	void PrintLargestWord() {
		string largestWord = FindLargestWord();
		gotoRowCol(37, 60);
		cout << "Largest Word: " << largestWord;
	}


	void WriteWordToFile(const char& character) {
		ofstream wordFile("Words.txt", ios::app);  // Open in append mode
		if (wordFile.is_open()) {
			if (character == '\n') {
				wordFile << endl;
			}
			else if (character == '\b') {  // Backspace key
				// Move the file cursor one position back
				wordFile.seekp(-1, ios::cur);
				// Erase the character by writing a space over it
				wordFile << ' ';
			}
			else {
				wordFile << character;
			}
			wordFile.close();
		}
		else {
			cout << "Error opening word file" << endl;
		}
	}


	int PrintParagraphCountFromFile() {
		ifstream wordFile("Words.txt");
		if (!wordFile.is_open()) {
			cout << "Error opening word file" << endl;
			return 0;
		}

		int paragraphCount = 0;
		string line;
		while (getline(wordFile, line)) {
			if (line.empty()) {
				// Check for two consecutive newlines to determine a paragraph break
				string nextLine;
				if (getline(wordFile, nextLine) && nextLine.empty()) {
					paragraphCount++;
				}
			}
		}

		wordFile.close();
		gotoRowCol(40, 0);
		return paragraphCount;
	}
public:
	list<list<char>> text;
	list<list<char>>::iterator row_iterator;
	list<char>::iterator col_iterator;
	int CurrRow, CurrCol;
	deque<state>undo;
	stack<state>redo;
	CurrentFile() {
		text.push_back(list<char>());
		row_iterator = text.begin();
		(*row_iterator).push_back(' ');
		col_iterator = (*row_iterator).begin();
		CurrRow = CurrCol = 0;
	}
	state saveState() {
		state* s = new state;
		s->text.push_back(list<char>());
		auto r_itr = s->text.begin();
		for (auto row = text.begin(); row != text.end(); row++, r_itr++) {
			s->text.push_back(list<char>());
			for (auto col = (*row).begin(); col != (*row).end(); col++) {
				char ch = *col;
				(*r_itr).push_back(ch);
			}
		}
		s->row_iterator = s->text.begin();
		s->col_iterator = (*s->row_iterator).begin();
		s->col = CurrCol;
		s->row = CurrRow;
		return *s;
	}
	void loadState(state s) {
		text = s.text;
		row_iterator = text.begin();
		CurrCol = s.col;
		CurrRow = s.row;
		for (int row = 0; row < s.row; row++)
			row_iterator++;
		col_iterator = (*row_iterator).begin();
		for (int col = 0; col < s.col; col++)
			col_iterator++;
	}
	void Choice(ifstream& Rdr) {
		int choice = -1;
		int R = 0, C = 0;
		gotoRowCol(1, 60);
		cout << "Text Editor By Haris Majeed Raja & Mudassir Hussain";


		gotoRowCol(10, 80);
		cout << "    New File    " << endl;

		gotoRowCol(15, 80);
		cout << "    Open File    " << endl;


		gotoRowCol(20, 80);
		cout << "    Merge Files   " << endl;


		gotoRowCol(25, 80);
		cout << "    Exit    " << endl;


		while (choice == -1) {
			getRowColbyLeftClick(R, C);
			if ((R >= 9 && R <= 11) && (C >= 80 && C <= 136))
				choice = 1;
			if ((R >= 14 && R <= 16) && (C >= 80 && C <= 136))
				choice = 2;
			if ((R >= 19 && R <= 21) && (C >= 80 && C <= 136))
				choice = 3;
			if ((R >= 24 && R <= 26) && (C >= 80 && C <= 136))
				choice = 4;
		}
		switch (choice) {
		case 1:
			Create_File();
			break;
		case 2:
			Open_File();
			break;
		case 3:
			MergeFiles();
			break;
		case 4:
			Closing(Rdr);
			exit(1);
			break;
		}
	}
	void Closing(ifstream & Rdr) {
		Rdr.close();
		ofstream wrt;
		wrt.open("Save_File.txt");
		for (auto i = Files.begin(); i != Files.end(); i++) {
			wrt << (*i) << endl;
		}
		ofstream clearFile("Words.txt", ios::trunc);
		//for (auto i = Passwords.begin(); i != Passwords.end(); i++) {
		//	wrt << (*i) << endl;
		//}
		wrt.close();
	}
	void Create_File() {
		system("cls");
		string fileName;
		cout << "Enter File name: ";
		cin >> fileName;

		// Check if the file already exists
		if (find(Files.begin(), Files.end(), fileName) != Files.end()) {
			cout << "File already exists" << endl;
			return;
		}

		//// Get and set the password for the file
		//string pass;
		//cout << "\nEnter a password for this file: ";
		//cin >> pass;

		//// Save the password for the current file
		//password = pass;

		Files.push_back(fileName);
		//Passwords.push_back(pass);

		ofstream wrt(fileName.c_str());
		//ofstream w(pass.c_str());
		system("cls");
		Edit_File(wrt);
		system("cls");
		system("color 09");
		wrt.close();
	}

	//void Create_file() {
	//	system("cls");
	//	string fileName, password;
	//	cout << "Enter File name: ";
	//	cin >> fileName;
	//	// Check if the file already exists
	//	if (find_if(Files.begin(), Files.end(), [fileName](const auto& file) { return file.first.first == fileName; }) != Files.end()) {
	//		cout << "File already exists" << endl;
	//		return;
	//	}
	//	// Prompt for and get the password for the file
	//	cout << "\nEnter a password for this file: ";
	//	cin >> password;
	//	L.push_back({ fileName, password });
	//	ofstream wrt(fileName.c_str());
	//	system("cls");
	//	Edit_File(wrt);
	//	system("cls");
	//	system("color 09");
	//	wrt.close();
	//}

	void Open_File() {
		system("cls");
		string fileName;
		cout << "Enter File name: ";
		cin >> fileName;

		// Check if the file exists
		auto fileIt = find(Files.begin(), Files.end(), fileName);
		if (fileIt == Files.end()) {
			cout << "File does not exist" << endl;
			return;
		}

		// Get the index of the file
		////int fileIndex = distance(Files.begin(), fileIt);
		//// Get the password for the file
		//string pass;
		//cout << "\nEnter the password to open that file: ";
		//cin >> pass;
		//// Check if the entered password matches the saved password
		//bool passwordMatch = false;
		//auto passIt = Passwords.begin();
		//for (int i = 0; i < fileIndex; ++i) {
		//	++passIt;
		//}
		//if (*passIt == pass) {
		//	passwordMatch = true;
		//}
		//if (!passwordMatch) {
		//	cout << "Password does not match" << endl;
		//	return;
		//}


		ifstream rdr(fileName.c_str());
		//ifstream r(pass.c_str());
		OpenSavedFile(rdr);
		rdr.close();
		ofstream wrt(fileName.c_str());
		system("cls");
		print();
		gotoRowCol(CurrRow, CurrCol);
		Edit_File(wrt);
		system("cls");
		system("color 09");
	}

	//void Open_file() {
	//	system("cls");
	//	string fileName, password;
	//	cout << "Enter File name: ";
	//	cin >> fileName;
	//	// Check if the file exists
	//	auto fileIt = find_if(Files.begin(), Files.end(), [fileName](const auto& file) { return file.first.first == fileName; });
	//	if (fileIt == Files.end()) {
	//		cout << "File does not exist" << endl;
	//		return;
	//	}
	//	// Prompt for the password for the file
	//	cout << "\nEnter the password to open that file: ";
	//	cin >> password;
	//	auto filePass = find_if(Files.begin(), Files.end(), [password](const auto& file) { return file.second.second == password; });
	//	// Check if the entered password matches the saved password
	//	if (filePass == Files.end()) {
	//		cout << "Pass does not exist" << endl;
	//		return;
	//	}
	//	ifstream rdr(fileName.c_str());
	//	OpenSavedFile(rdr);
	//	rdr.close();
	//	ofstream wrt(fileName.c_str());
	//	system("cls");
	//	print();
	//	gotoRowCol(CurrRow, CurrCol);
	//	Edit_File(wrt);
	//	system("cls");
	//	system("color 09");
	//}

	void Edit_File(ofstream& wrt) {
		system("color F0");
		char col;
		col = _getch();
		gotoRowCol(CurrRow, CurrCol);
		cout << col;
		(*col_iterator) = col;
		WriteWordToFile(col);
		CurrCol++;
		while (true) {
			if (CurrRow == 0)
				gotoRowCol(CurrRow, CurrCol);
			else
				gotoRowCol(CurrRow, CurrCol + 1);
			col = _getch();
			if (col == -32) {
			A:
				col = _getch();
				if (col == 72)//up arrow key
				{
					if (CurrRow == 0)
						continue;
					row_iterator--;
					col_iterator = (*row_iterator).begin();
					CurrRow--; 
					CurrCol = 0;
				}
				else if (col == 80) {//down arrow key
					row_iterator++;
					col_iterator = (*row_iterator).begin();
					CurrRow++; 
					CurrCol = 0;
				}
				else if (col == 75)//left arrow key
				{
					if (CurrCol -1 > 0) {
						col_iterator--;
						CurrCol--;
					}
				}
				else if (col == 77)//right arrow key
				{
					if (CurrCol == 159)
						continue;
					col_iterator++;
					CurrCol++;
				}
				else if (col == 83)//del button
				{
					auto temp = col_iterator;
					col_iterator++;
					(*row_iterator).erase(col_iterator);
					col_iterator = temp;
					system("cls");
					print();
					UpdateUndo();
				}
				if (CurrCol == 0) {
					gotoRowCol(CurrRow, 0);
					col = _getch();
					if (col == -32)
						goto A;
					(*row_iterator).push_front(col);
					col_iterator = (*row_iterator).begin();
					CurrCol = 1;
					system("cls");
					print();
					UpdateUndo();
				}
				continue;
			}
			else if (col == 13)//enter key
			{
				auto temp = row_iterator;
				row_iterator++;
				text.insert(row_iterator, list<char>());
				row_iterator = ++temp;
				CurrRow++; CurrCol = 0;
				gotoRowCol(CurrRow, CurrCol);
				col = _getch();
				if (col == -32)//if arrow or del key
					goto A;
				(*row_iterator).push_back(col);
				col_iterator = (*row_iterator).begin();

				WriteWordToFile('\n');
				system("cls");
				print();
				UpdateUndo();
				continue;
			}
			else if (col == 8)//backspace key
			{
				if (CurrCol == 0) {
					gotoRowCol(CurrRow, 0);
					col = _getch();
					if (col == -32)
						goto A;
					if (col == 8)
						continue;
					(*col_iterator) = col;
					col_iterator = (*row_iterator).begin();
					CurrCol = 1;
					continue;
				}
				auto temp = --col_iterator;
				col_iterator++;
				(*row_iterator).erase(col_iterator);
				col_iterator = temp;
				CurrCol--;
				WriteWordToFile('\b');
				system("cls");
				print();
				UpdateUndo();
				continue;
			}
			else if (col == 26) //undo button
			{
				if (!undo.empty()) {
					state s = undo.back();
					loadState(s);
					redo.push(undo.back());
					undo.pop_back();
					system("cls");
					print();
				}
				continue;
			}
			else if (col == 25) //redo button
			{
				if (!redo.empty()) {
					undo.push_back(redo.top());
					state s = redo.top();
					redo.pop();
					loadState(s);
					system("cls");
					print();
				}
				continue;
			}
			else if (col == 21) // Ctrl + U
			{
				ConvertToUppercase();
				continue;
			}
			else if (col == 12) // Ctrl + L
			{
				ConvertToLowercase();
				continue;
			}
			else if (col == 6) // Ctrl + F
			{
				auto temp = col_iterator;
				auto tem = row_iterator;
				int cr = CurrRow;
				int cc = CurrCol;
				string wordToFind;
				char c;
				gotoRowCol(38, 0);
				cout << "Enter the word to find: ";
				cin >> wordToFind;
				gotoRowCol(38, 100);
				cout << "Do you want case sensitive ? (y/n):";
				cin >> c;
				if (c == 'y' || c == 'Y') {
					if (FindWordCaseSens(wordToFind)) {
						gotoRowCol(39, 0);
						cout << "Word found!" << endl;
					}
					else {
						gotoRowCol(39, 0);
						cout << "Word not found!" << endl;
					}
				}
				else if (c == 'n' || c == 'N') {
					if (FindWordCaseInsens(wordToFind)) {
						gotoRowCol(39, 0);
						cout << "Word found!" << endl;
					}
					else {
						gotoRowCol(39, 0);
						cout << "Word not found!" << endl;
					}
				}
				col_iterator = temp;
				row_iterator = tem;
				CurrRow = cr;
				CurrCol = cc;
				Sleep(1500);
				system("cls");
				print();
				continue;
			}
			else if (col == 19) // Ctrl + S
			{
				auto temp = col_iterator;
				auto tem = row_iterator;
				int cr = CurrRow;
				int cc = CurrCol;
				string sentenceToFind;
				gotoRowCol(38, 0);
				cout << "Enter the sentence to find: ";
				cin.ignore(); // Ignore any previous newline character in the input buffer
				getline(cin, sentenceToFind);

				if (FindSentence(sentenceToFind)) {
					gotoRowCol(39, 0);
					cout << "Sentence found !!" << endl;
				}
				else {
					gotoRowCol(39, 0);
					cout << "Sentence not found !!" << endl;
				}
				col_iterator = temp;
				row_iterator = tem;
				CurrRow = cr;
				CurrCol = cc;
				Sleep(1500);
				system("cls");
				print();
				continue;
			}
			else if (col == 18) // Ctrl + R
			{
				string targetWord, newWord;
				gotoRowCol(38, 0);
				cout << "Enter the word to replace with: ";
				cin >> targetWord;
				gotoRowCol(39, 0);
				cout << "Enter the new word: ";
				cin >> newWord;
				char c;
				cout << "Do you want to replace all words: (y/n) ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					ReplaceAllWords(targetWord, newWord);
				else
					ReplaceOnlyFirstWord(targetWord, newWord);
				system("cls");
				print();
				UpdateUndo();
				continue;
			}
			else if (col == 20) // Ctrl + T for find and replace from current cursor position
			{
				string targetWord, newWord;
				gotoRowCol(38, 0);
				cout << "\nEnter the word to replace with: ";
				cin >> targetWord;
				gotoRowCol(39, 0);
				cout << "Enter the new word: ";
				cin >> newWord;
				char c;
				cout << "\nDo you want to replace all ? (y/n): ";
				cin >> c;
				if(c=='y'||c=='Y')
					FindAndReplaceAll(targetWord, newWord);
				else
					FindAndReplaceNext(targetWord, newWord);
				continue;
			}
			else if (col == 7) // Ctrl + G
			{
				auto temp = col_iterator;
				auto tem = row_iterator;
				int cr = CurrRow;
				int cc = CurrCol;
				string substringToFind;
				gotoRowCol(38, 0);
				cout << "Enter the substring to find: ";
				cin.ignore(); // Ignore any previous newline character in the input buffer
				getline(cin, substringToFind);

				if (FindSubstring(substringToFind)) {
					gotoRowCol(39, 0);
					cout << "Substring found !!" << endl;
				}
				else {
					gotoRowCol(39, 0);
					cout << "Substring not found !!" << endl;
				}
				col_iterator = temp;
				row_iterator = tem;
				CurrRow = cr;
				CurrCol = cc;
				Sleep(1500);
				system("cls");
				print();
				continue;
			}
			else if (col == 11) // Ctrl + K
			{
				auto temp = col_iterator;
				auto tem = row_iterator;
				int cr = CurrRow;
				int cc = CurrCol;
				string substringToFind;
				gotoRowCol(38, 0);
				cout << "Enter the substring to find count: ";
				cin.ignore(); // Ignore any previous newline character in the input buffer
				getline(cin, substringToFind);
				gotoRowCol(39, 0);
				cout <<"Count of "<<substringToFind<<" : "<< CountSubstring(substringToFind);
				col_iterator = temp;
				row_iterator = tem;
				CurrRow = cr;
				CurrCol = cc;
				Sleep(1500);
				system("cls");
				print();
				continue;
			}
			else if (col == 23)  {//Cntrl+W
				cout << "\n\nLargest Word is: " << FindLargestWord();
				vector<string> smallWords{};
				smallWords=generateWordsFromFile(FindLargestWord());
				if (smallWords.size() == 0) {
					cout << "\nNo small words can be formed with it";
				}
				else {
					cout << "\nSmaller Words are :";
					for (auto Words : smallWords) {
						cout << Words << " ";
					}
				}
				continue;
			}
			else if (col == 28) // Ctrl + backslash ('\') for adding prefix
			{
				string targetWord, prefix;
				gotoRowCol(38, 0);
				cout << "Enter the word to add prefix: ";
				cin >> targetWord;
				gotoRowCol(39, 0);
				cout << "Enter the prefix: ";
				cin >> prefix;

				AddPrefixToWord(targetWord, prefix);
				system("cls");
				print();
				UpdateUndo();
				continue;
			}
			else if (col == 28 && GetAsyncKeyState(VK_SHIFT) & 0x8000) // Ctrl + Shift + backslash ('\') for adding postfix
			{
				string targetWord, postfix;
				cout << "\nEnter the word to add postfix: ";
				cin >> targetWord;
				cout << "Enter the postfix: ";
				cin >> postfix;

				AddPostfixToWord(targetWord, postfix);
				system("cls");
				print();
				UpdateUndo();
				continue;
			}
			else if (col == 27)//esc to close 
			{
				writeTextToFile(wrt);
				break;
			}
			if (CurrCol == 100) {
				text.push_back(list<char>());
				row_iterator++;
				CurrCol = 0;
				CurrRow++;
				(*row_iterator).push_back(col);
				col_iterator = (*row_iterator).begin();
			}
			else {
				auto temp = col_iterator;
				col_iterator++;
				(*row_iterator).insert(col_iterator, col);
				col_iterator = ++temp;
				CurrCol++;
				WriteWordToFile(col);
			}
			system("cls");
			print();
			UpdateUndo();
		}
		system("Color 07");
	}
	void print() {
		for (auto row = text.begin(); row != text.end(); row++) {
			for (auto col = (*row).begin(); col != (*row).end(); col++)
				cout << *col;
			cout << endl;
		}
		PrintSpecialCharacterCount();
		//PrintWordsLength();
		PrintWordsCount();
		PrintLargestWordLength();
		PrintSmallestWordLength();
		PrintSentenceCount();
		PrintAvgWordLength();
		PrintSmallestWord();
		PrintLargestWord();
		PrintLargestWordParaCount();
		//PrintWordWithMostWords();
	}
	void writeTextToFile(ofstream& wrt) {
		for (auto row = text.begin(); row != text.end(); row++) {
			for (auto col = (*row).begin(); col != (*row).end(); col++)
				wrt << *col;
			wrt << '\n';
		}
	}

	void openSavedFile(ifstream& rdr) {
		char ch;
		(*row_iterator).clear();
		while (!rdr.eof()) {
			rdr.get(ch);
			if (ch != '\n') {
				(*row_iterator).push_back(ch);
			}
			else {
				text.push_back(list<char>());
				row_iterator++;
			}
		}
		row_iterator = text.begin();
		col_iterator = (*row_iterator).begin();
		CurrRow = 0, CurrCol = 0;
		gotoRowCol(CurrRow, CurrCol);
	}
	
	void OpenSavedFile(ifstream& rdr) {
		const int maxAttempts = 3;
		int attempts = 0;

		while (attempts < maxAttempts) {
			string password;
			cout << "Enter password: ";
			cin >> password;
			if (CheckPassword(password)) {
				char ch;
				(*row_iterator).clear();
				while (!rdr.eof()) {
					rdr.get(ch);
					if (ch != '\n')
						(*row_iterator).push_back(ch);
					else {
						text.push_back(list<char>());
						row_iterator++;
					}
				}
				row_iterator = text.begin();
				col_iterator = (*row_iterator).begin();
				CurrRow = 0, CurrCol = 0;
				gotoRowCol(CurrRow, CurrCol);
				return;
			}
			else {
				cout << "Incorrect password. " << maxAttempts - attempts - 1 << " attempts remaining." << endl;
				attempts++;
				if (attempts < maxAttempts)
					continue;
				else {
					cout << "Max attempts reached. Access denied." << endl;
					exit(1);
				}
			}
		}
	}

	bool CheckPassword(const string& pass) {
		return pass == "HnM";
	}
	void UpdateUndo() {
		state s = saveState();
		undo.push_back(s);
	}
	void ConvertToUppercase() {
		state s = saveState();
		auto start = col_iterator;
		while (start != (*row_iterator).begin() && isalpha(*(start)))
			start--;
		auto end = col_iterator;
		while (end != (*row_iterator).end() && isalpha(*end))
			end++;
		for (auto it = start; it != end; it++)
			*it = toupper(*it);
		system("cls");
		print();
		UpdateUndo();
	}
	void ConvertToLowercase() {
		state s = saveState();
		auto start = col_iterator;
		while (start != (*row_iterator).begin() && isalpha(*(start)))
			start--;
		auto end = col_iterator;
		while (end != (*row_iterator).end() && isalpha(*end))
			end++;
		for (auto it = start; it != end; it++)
			*it = tolower(*it);
		system("cls");
		print();
		UpdateUndo();
	}
	void AddPrefixToWord(string &targetWord,string&prefix) {
		auto row = text.begin();
		while (row != text.end()) {
			auto findWord = search((*row).begin(), (*row).end(), targetWord.begin(), targetWord.end());
			while (findWord != (*row).end() && distance((*row).begin(), findWord) + targetWord.size() <= (*row).size()) {
				auto itr = next(findWord, targetWord.size());
				(*row).insert(findWord, prefix.begin(), prefix.end());
				findWord = search(itr, (*row).end(), targetWord.begin(), targetWord.end());
			}
			row++;
		}
	}
	void AddPostfixToWord(string& targetWord, string& postfix) {
		auto row = text.begin();
		while (row != text.end()) {
			auto findWord = search((*row).begin(), (*row).end(), targetWord.begin(), targetWord.end());
			while (findWord != (*row).end() && distance((*row).begin(), findWord) + targetWord.size() <= (*row).size()) {
				auto itr = next(findWord, targetWord.size());
				(*row).insert(itr, postfix.begin(), postfix.end());
				findWord = search(itr, (*row).end(), targetWord.begin(), targetWord.end());
			}
			row++;
		}
	}
	bool FindWordCaseSens(const string& word) {
		for (auto row = text.begin(); row != text.end(); ++row) {
			for (auto col = (*row).begin(); col != (*row).end(); ++col) {
				auto it = col;
				auto wordIt = word.begin();
				while (it != (*row).end() && wordIt != word.end() && *it == *wordIt) {
					++it;
					++wordIt;
				}
				if (wordIt == word.end())
					return true;
			}
		}
		return false;
	}	
	bool FindWordCaseInsens(const string& word) {
		for (auto row = text.begin(); row != text.end(); ++row) {
			for (auto col = (*row).begin(); col != (*row).end(); ++col) {
				auto it = col;
				auto wordIt = word.begin();
				while (it != (*row).end() && wordIt != word.end() && tolower(*it) == tolower(*wordIt)) {
					++it;
					++wordIt;
				}
				if (wordIt == word.end()) {
					return true;
				}
			}
		}
		return false;
	}
	bool FindSentence(const string& sentence) {
		for (auto row = text.begin(); row != text.end(); ++row) {
			auto col = (*row).begin();
			auto sentenceIt = sentence.begin();
			while (col != (*row).end() && sentenceIt != sentence.end() && *col == *sentenceIt) {
				++col;
				++sentenceIt;
			}
			if (sentenceIt == sentence.end()) {
				// Set the current position to the start of the matched sentence
				/*row_iterator = row;
				col_iterator = col;
				CurrRow = distance(text.begin(), row);
				CurrCol = distance((*row).begin(), col);
				gotoRowCol(CurrRow, CurrCol);*/
				return true;
			}
			else if (sentenceIt != sentence.end() && col != (*row).end() && isspace(*sentenceIt) && isspace(*col)) {
				++sentenceIt;
				continue;
			}
			else {
				++sentenceIt;
				while (sentenceIt != sentence.end() && isspace(*sentenceIt))
					++sentenceIt;
			}
		}
		return false;
	}
	bool FindSubstring(const string& substring) {
		for (auto row = text.begin(); row != text.end(); ++row) {
			for (auto col = (*row).begin(); col != (*row).end(); ++col) {
				auto it = col;
				auto substringIt = substring.begin();
				while (it != (*row).end() && substringIt != substring.end() && *it == *substringIt) {
					++it;
					++substringIt;
				}
				if (substringIt == substring.end()) {
					/*row_iterator = row;
					col_iterator = col;
					CurrRow = distance(text.begin(), row);
					CurrCol = distance((*row).begin(), col);
					gotoRowCol(CurrRow, CurrCol);*/
					return true;
				}
			}
		}
		return false;
	}

	void ReplaceOnlyFirstWord(string& TargetWord, string& newWord) {
		state s = saveState();
		auto row = text.begin();
		while (row != text.end()) {
			auto findWord = search((*row).begin(), (*row).end(), TargetWord.begin(), TargetWord.end());
			if (findWord != (*row).end() && distance((*row).begin(), findWord) + TargetWord.size() <=(*row).size()) {
				auto newPosition = next((*row).begin(), distance((*row).begin(), findWord) + TargetWord.size());
				(*row).erase(findWord, newPosition);
				//insert kry new word ko
				(*row).insert(newPosition, newWord.begin(), newWord.end());
				//loop break kr dy aik word py kr ky
				break;
			}
			row++;
		}
		UpdateUndo();
	}
	void ReplaceAllWords(string &TargetWord,string &newWord) {
		state s = saveState();
		auto row = text.begin();
		while(row!=text.end()){
			auto findWord = search((*row).begin(), (*row).end(), TargetWord.begin(), TargetWord.end());
			while (findWord != (*row).end() && distance((*row).begin(), findWord) +TargetWord.size() <= (*row).size()) {
				auto newPosition = next(findWord, TargetWord.size());
				(*row).erase(findWord, newPosition);
				//aik py insert kry
				(*row).insert(newPosition, newWord.begin(), newWord.end());
				//phir baki words ky liye loop chalay
				findWord = search(newPosition, (*row).end(), TargetWord.begin(), TargetWord.end());
			}
			row++;
		}
		UpdateUndo();
	}
	bool FindAndReplace(const string& targetWord, const string& newWord, bool replaceAll = false) {
		state s = saveState();
		auto startRow = row_iterator;
		auto startCol = col_iterator;

		while (startRow != text.end()) {
			auto findWord = search(startCol, (*startRow).end(), targetWord.begin(), targetWord.end());
			if (findWord != (*startRow).end() && distance((*startRow).begin(), findWord) + targetWord.size() <= (*startRow).size()) {
				auto newPosition = next(findWord, targetWord.size());
				if (!replaceAll) {
					// Replace only the first occurrence and break
					(*startRow).erase(findWord, newPosition);
					(*startRow).insert(newPosition, newWord.begin(), newWord.end());
					col_iterator = newPosition;
					CurrCol = distance((*startRow).begin(), col_iterator);
					gotoRowCol(CurrRow, CurrCol);
					system("cls");
					print();
					UpdateUndo();
					return true;
				}
				else {
					// Replace all occurrences in the current row
					(*startRow).erase(findWord, newPosition);
					(*startRow).insert(newPosition, newWord.begin(), newWord.end());
					startCol = newPosition;
				}
			}
			else {
				// Move to the next row
				startRow++;
				startCol = (*startRow).begin();
			}
		}
		// If reached here, the word was not found
		return false;
	}
	void FindAndReplaceNext(const string& targetWord, const string& newWord) {
		if (FindAndReplace(targetWord, newWord)) {
			// If replacement was successful, move the cursor to the next occurrence
			system("cls");
			print();
			UpdateUndo();
		}
		else {
			gotoRowCol(CurrRow, CurrCol);
			cout << "Word not found!";
		}
	}
	void FindAndReplaceAll(const string& targetWord, const string& newWord) {
		if (FindAndReplace(targetWord, newWord, true)) {
			// If replacement was successful, move the cursor to the end of the file
			system("cls");
			print();
			UpdateUndo();
		}
		else {
			gotoRowCol(CurrRow, CurrCol);
			cout << "Word not found!";
		}
	}


	int FindLargestParagraphWordCount() {
		int maxWordCount = 0;
		for (const auto& paragraph : text) {
			int wordCount = 0;
			bool inWord = false;
			for (const char& ch : paragraph) {
				if (isalpha(ch)) {
					if (!inWord) {
						inWord = true;
						wordCount++;
					}
				}
				else
					inWord = false;
			}
			maxWordCount = max(maxWordCount, wordCount);
		}
		return maxWordCount;
	}
	int FindParagraphCount() {
		int paragraphCount = 0;
		bool inParagraph = false;
		for (auto row = text.begin(); row != text.end(); ++row) {
			if ((*row).empty()) {
				if (inParagraph) {
					paragraphCount++;
					inParagraph = false;
				}
			}
			else 
				inParagraph = true;
		}
		if (inParagraph)
			paragraphCount++;
		return paragraphCount;
	}

	void PrintLargestWordParaCount() {
		int largestCount = FindLargestParagraphWordCount();
		gotoRowCol(35, 140);
		cout << "Largest Para Word Count: " << largestCount;
		int count = PrintParagraphCountFromFile();
		gotoRowCol(36, 140);
		cout << "Para Count: " << count+1;
	}

	
	
	vector<string> generateWordsFromFile(const string& LargestWord) {
		vector<string> v{};
		ifstream rdr("Words.txt");
		if (!rdr.is_open()) {
			cout << "Error opening word file" << endl;
			return v;
		}
		string word;
		set<string> smallerWords;
		while (rdr >> word) {
			string tempLargestWord = LargestWord;
			bool isValidWord = true;
			for (char letter : word) {
				int found = tempLargestWord.find(letter);
				if (found != string::npos)
					tempLargestWord.erase(found, 1);//1 is the count
				else {
					isValidWord = false;
					break;
				}
			}
			if (isValidWord)
				smallerWords.insert(word);
		}
		rdr.close();
		smallerWords.erase(LargestWord);
		for (const string& Word : smallerWords)
			v.push_back(Word);
		return v;
	}



	void EncodeFile(const unordered_map<char, char>& encodingMap) {
		ofstream processedFile("ProcessedFileEncoded.txt");

		for (auto row = text.begin(); row != text.end(); ++row) {
			for (auto col = (*row).begin(); col != (*row).end(); ++col) {
				char originalChar = *col;
				auto encodingIt = encodingMap.find(originalChar);
				if (encodingIt != encodingMap.end()) {
					char encodedChar = encodingIt->second;
					processedFile << encodedChar;
				}
				else {
					processedFile << originalChar;
				}
			}
			processedFile << endl;
		}
		processedFile.close();
	}

	// Function to read encodings from a file
	unordered_map<char, char> ReadEncodingsFromFile(const string& encodingFileName) {
		ifstream encodingFile(encodingFileName);
		unordered_map<char, char> encodingMap;

		char originalChar, encodedChar;
		while (encodingFile >> originalChar >> encodedChar) {
			encodingMap[originalChar] = encodedChar;
		}

		encodingFile.close();
		return encodingMap;
	}


	void MergeFiles() {
		system("cls");
		string fileName1, fileName2, newFileName;
		cout << "Enter the name of the first file: ";
		cin >> fileName1;
		cout << "Enter the name of the second file: ";
		cin >> fileName2;
		ifstream file1(fileName1.c_str());
		ifstream file2(fileName2.c_str());
		if (!file1.is_open() || !file2.is_open()) {
			cout << "Error: Unable to open files for merging." << endl;
			return;
		}

		cout << "Enter the name of the new file: ";
		cin >> newFileName;
		ofstream mergedFile(newFileName);
		if (!mergedFile.is_open()) {
			cout << "Error: Unable to open the new file for writing." << endl;
			file1.close();
			file2.close();
			return;
		}

		MergeTwoFiles(file1, mergedFile);
		MergeTwoFiles(file2, mergedFile);
		cout << "Files merged successfully into " << newFileName << endl;

		Files.push_back(newFileName);

		ofstream wrt(newFileName.c_str());
		system("cls");
		wrt.close();

		file1.close();
		file2.close();
		mergedFile.close();

	}

	void MergeTwoFiles(ifstream& file1, ofstream& mergedFile) {
		char ch;
		while (file1.get(ch)) {
			mergedFile.put(ch);
		}
	}

};
void input(ifstream& rdr) {
	string file_name,pass;
	rdr >> file_name;
	while (!rdr.eof()) {
		Files.push_back(file_name);
		rdr >> file_name;
	}
}
int main() {
	system("color 09");
	int row =0, col = 0;
	CurrentFile N;
	ifstream rdr;
	ofstream wrt;
	rdr.open("Save_File.txt");
	
	input(rdr);
	while (true) {
		N.Choice(rdr);
	}
	rdr.close();
	return _getch();
}