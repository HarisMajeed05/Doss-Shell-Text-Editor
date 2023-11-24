#pragma once
#include"Folder.h"
class Tree
{
public:
	folder* root;
	folder* currentfolder;
	Tree()
	{
		currentfolder = root = new folder("V");
	}
	void insert(folder* f)
	{
		currentfolder->folders.push_back(f);
	}
	void setpath(folder* f)
	{
		string path = currentfolder->name;
		folder* parent = new folder();
		while (parent != nullptr)
		{
			path = parent->name + "/" + path;
			parent = parent->parent;

		}
		f->path = path;
	}
	void print(string prompt = "\\>")
	{
		if (currentfolder->name == "V")
		{
			cout<<"V:"<<prompt;
		}
		else
		{
			cout << "V:" << currentfolder->path.substr(2, currentfolder->path.length()) << "\\" << currentfolder->name << prompt;
		}
	}
	bool folder_exist(string name)
	{
		for (int i = 0; i < currentfolder->folders.size(); i++)
		{
			if (currentfolder->folders[i]->name == name)
			{
				return true;
			}
		}
		return false;
	}
	file* Find_file(string name)
	{
		for (int i = 0; i < currentfolder->files.size(); i++)
		{
			if (currentfolder->files[i]->name == name)
			{
				return currentfolder->files[i];
			}
		}
		return nullptr;
	}
	folder* find_folder(string name)
	{
		for (int i = 0; i < currentfolder->folders.size(); i++)
		{
			if (currentfolder->folders[i]->name == name)
			{
				return currentfolder->folders[i];
			}
		}
		return nullptr;
	}
	bool checkfileindir(string name)
	{
		for (int i = 0; i < currentfolder->files.size(); i++)
		{
			if (currentfolder->files[i]->name == name)
			{
				return true;
			}
		}
		return false;
	}

	void searchInAllFiles(const std::string& searchString) const 
	{
		searchInFilesRecursive(currentfolder, searchString);
	}

private:
	// Recursive helper function for searching in files
	void searchInFilesRecursive(const folder* current, const std::string& searchString) const 
	{
		// Search in files of the current folder
		for (const file* f : current->files) 
		{
			if (f->searchInFile(searchString))
			{
				std::cout << "Text found in file " << f->name << ": " << searchString << std::endl;
			}
		}

		// Recursively search in files of subfolders
		for (const folder* subfolder : current->folders)
		{
			searchInFilesRecursive(subfolder, searchString);
		}
	}

};