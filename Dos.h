#pragma once
#include"Tree.h"
class DOS
{
private:
	string lower(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] == tolower(str[i]);
		}
		return str;
	}
	bool prompt = false;
public:
	Tree tree;
	string user = "Adul Rehman";
	DOS(){}
	void print()
	{
		cout << "\t\t\t\t\t" << "M Haris | Mudassir | Bscs22017 | DSA-ITU-2023" << endl << endl;
		
	}
	void run()
	{
		print();
		bool exit = false;
		while (!exit)
		{
			tree.print();
			exit = input();

		}
	}
	void writeDataToFile(const std::string& command)
	{
		// Extract file name and data from the command
		size_t spaceIndex = command.find(' ');
		if (spaceIndex != std::string::npos && spaceIndex + 1 < command.length()) {
			std::string fileName = command.substr(spaceIndex + 1, command.find(' ', spaceIndex + 1) - spaceIndex - 1);
			std::string newData = command.substr(command.find(' ', spaceIndex + 1) + 1);

			// Find the file based on name
			file* f = tree.Find_file(fileName);

			if (f) {
				// Write data to the file
				f->writeData(newData);
				std::cout << "Data written to file " << fileName << std::endl;
			}
			else {
				std::cout << "File not found: " << fileName << std::endl;
			}
		}
		else {
			std::cout << "Invalid command format. Usage: write <file_name> <data>" << std::endl;
		}
	}
	void findStringInFiles(const string& command)
	{
		// Extract the string to find from the command
		size_t spaceIndex = command.find(' ');
		if (spaceIndex != string::npos && spaceIndex + 1 < command.length())
		{
			string searchString = command.substr(spaceIndex + 1);

			// Iterate through files in the current virtual directory
			for (file* f : tree.currentfolder->files)
			{
				// Check if the file contains the search string
				if (f->data.find(searchString) != string::npos)
				{
					cout << "Found in file: " << f->name << endl;
				}
			}
		}
		else
		{
			cout << "Invalid command format. Usage: findstr <search_string>" << endl;
		}
	}
	void findDataInFile(const std::string& command)
	{
		// Extract file name and data from the command
		size_t spaceIndex = command.find(' ');
		if (spaceIndex != std::string::npos && spaceIndex + 1 < command.length()) {
			std::string fileName = command.substr(spaceIndex + 1, command.find(' ', spaceIndex + 1) - spaceIndex - 1);
			std::string newData = command.substr(command.find(' ', spaceIndex + 1) + 1);

			// Find the file based on name
			file* f = tree.Find_file(fileName);

			if (f)
			{
				// Write data to the file
				if (f->searchInFile(newData))
				{
					cout << "Data found in File" << endl;
				}
				else
				{
					cout << "Data is not is File" << endl;
				}
			}
			else {
				std::cout << "File not found: " << fileName << std::endl;
			}
		}
		else {
			std::cout << "Invalid command format. Usage: write <file_name> <data>" << std::endl;
		}
	}
	bool input()
	{
		string command;
		getline(cin, command);
		string opr = command.substr(0, command.find(' '));
		opr = lower(opr);
		if (opr == "mkdir")
		{
			tree.insert(new folder(command.substr(6, command.length()), tree.currentfolder->path + "\\" + tree.currentfolder->name, tree.currentfolder));
		}

		else if (opr == "create")
		{
			file* f = new file(command.substr(7, command.length()), user);
			tree.currentfolder->files.push_back(f);
		}
		else if (opr == "del")
		{
			tree.currentfolder->remove_file(command.substr(4, command.length()));
		}
		else if (opr == "cd")
		{
			string folder = command.substr(3, command.length());
			if (tree.folder_exist(folder))
			{
				tree.currentfolder = tree.find_folder(folder);
			}
			else
			{
				cout << " No such directory available" << endl;
			}
		}
		else if (opr == "convert")
		{
			// Extract source and destination file types
			size_t spaceIndex = command.find(' ');
			if (spaceIndex == string::npos)
			{
				cout << "Invalid CONVERT command. Usage: CONVERT <source_type> <destination_type>" << endl;
				return false;
			}

			string sourceType = command.substr(spaceIndex + 1, command.find(' ', spaceIndex + 1) - spaceIndex - 1);
			string destType = command.substr(command.find(' ', spaceIndex + 1) + 1);

			// Check if both source and destination types are provided
			if (sourceType.empty() || destType.empty())
			{
				cout << "Invalid CONVERT command. Usage: CONVERT <source_type> <destination_type>" << endl;
				return false;
			}

			// Iterate through files in the current directory and convert file types
			for (file* f : tree.currentfolder->files)
			{
				size_t dotIndex = f->name.find_last_of('.');
				if (dotIndex != string::npos)
				{
					string fileType = f->name.substr(dotIndex + 1);
					if (fileType == sourceType)
					{
						// Change file type to destination type
						f->name.replace(dotIndex + 1, string::npos, destType);
						f->type = destType;
					}
				}
			}

			cout << "File types converted from " << sourceType << " to " << destType << endl;
		}

		else if (opr == "write")
		{
			writeDataToFile(command);
		}
		else if (opr == "cd..")
		{
			if (tree.currentfolder->parent != nullptr)
			{
				tree.currentfolder = tree.currentfolder->parent;
			}
		}
		else if (opr == "cd\\")
		{
			if (tree.currentfolder->parent != nullptr)
			{
				tree.currentfolder = tree.root;
			}
		}
		else if (opr == "dir" || opr == "cd.")
		{
			tree.currentfolder->print();
		}
		else if (opr == "cls")
		{
			system("cls");
			print();
		}
		else if (opr == "exist")
		{
			return true;
		}
		else if (opr == "find")
		{
			string name = command.substr(5, command.length());
			if (tree.checkfileindir(name))
			{
				cout << " File is in current dir " << endl;
			}
			else
			{
				cout << " File not found in directory " << endl;
			}
		}
		else if (opr == "findstr")
		{
			// Call a function to handle FINDSTR command
			findStringInFiles(command);
		}
		else if (opr == "Data")
		{
			string name = command.substr(5, command.length());
			file* t = tree.Find_file(name);
			cout << t ->data<<endl;
		}
		else if (opr == "attrib")
		{
			string name = command.substr(7, command.length());

			// Check if the file name contains a dot (.)
			size_t dotIndex = name.find_last_of('.');
			if (dotIndex == string::npos) {
				cout << "Invalid file name format. Please include the file type." << endl;
				return false;
			}

			// Extract the file type and name
			string typeName = name.substr(dotIndex + 1);
			string fileName = name.substr(0, dotIndex);

			// Find the file based on name and type
			file* f = tree.Find_file(name);

			// If the file is not found, print an error message
			if (!f) {
				cout << "File not found: " << name << endl;
				return false;
			}

			// Print attributes
			f->print();;
		}
		else if (opr == "format")
		{
			tree.currentfolder->emptydir();
		}
		else if (opr == "rmdir")
		{
			folder* current = tree.currentfolder;
			tree.currentfolder = tree.currentfolder->parent;
			tree.currentfolder->remove_folder(current->name);
		}
		else if (opr == "prompt")
		{
			prompt = !prompt;
		}
		else if (opr == "findf") 
		{
			findDataInFile(command);
		}
		else if (opr == "rename")
		{
			command = command.substr(opr.length() + 1, command.length());
			string currname = command.substr(0, command.find(' '));
			string newname = command.substr(currname.length() + 1, command.length());
			file* f = tree.currentfolder->FindFile(currname);
			f->name = newname;
		}
		else if (opr == "copy")
		{
			command = command.substr(opr.length() + 3, command.length());
			int ind = command.find(' ');
			string sourcepath = command.substr(0, command.find(' '));
			string destpath = command.substr(sourcepath.length() + 3, command.length());
			file* file_to_copy;
			folder* currentfold = tree.root;
			string f;

			while (sourcepath.length() > 0)
			{
				f = sourcepath.substr(0, sourcepath.find('\\'));
				sourcepath = sourcepath.substr(f.length() + 1, sourcepath.length());
				if (sourcepath.length() != 0)
				{
					currentfold = currentfold->FindFolder(f);
				}
				if (currentfold == nullptr)
				{
					cout << "Path was not found";
					return true;
				}

			}
			file_to_copy = currentfold->FindFile(f);

			currentfold = tree.root;
			while (destpath.length() > 0)
			{
				f = destpath.substr(0, destpath.find('\\'));
				destpath = destpath.substr(f.length() + 1, destpath.length());
				currentfold = currentfold->FindFolder(f);
				if (currentfold == nullptr)
				{
					cout << "Path was not found";
					return true;
				}
			}
			currentfold->insertfile(file_to_copy);
		}
		else if (opr == "mov")
		{
			command = command.substr(opr.length() + 3, command.length());
			int ind = command.find(' ');
			string sourcepath = command.substr(0, command.find(' '));
			string destpath = command.substr(sourcepath.length() + 3, command.length());
			file* file_to_copy;
			folder* currentfold = tree.root;
			string f;

			while (sourcepath.length() > 0)
			{
				f = sourcepath.substr(0, sourcepath.find('\\'));
				sourcepath = sourcepath.substr(f.length() + 1, sourcepath.length());
				if (sourcepath.length() != 0)
				{
					currentfold = currentfold->FindFolder(f);
				}
				if (currentfold == nullptr)
				{
					cout << "Path was not found";
					return true;
				}

			}
			file_to_copy = currentfold->FindFile(f);
			currentfold->remove_file(file_to_copy->name);
			currentfold = tree.root;
			while (destpath.length() > 0)
			{
				f = destpath.substr(0, destpath.find('\\'));
				destpath = destpath.substr(f.length() + 1, destpath.length());
				currentfold = currentfold->FindFolder(f);
				if (currentfold == nullptr)
				{
					cout << "Path was not found";
					return true;
				}
			}
			currentfold->insertfile(file_to_copy);
			

		}

		else if (opr == "help")
		{
			cout << "mkdir\tMakes a new directory in current directory" << endl;
			cout << "cd\tChange the current directory" << endl;
			cout << "cd..\tMove back to previous directory" << endl;

		}

	/*	if (opr != "cls")
		{
			if (prompt)
			{
				tree.print("$");

			}
			else
			{
				tree.print();
			}
			
		}*/
		return false;
	}
		

};