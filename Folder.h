#pragma once
#include<string>
#include<iostream>
#include<ctime>
#include<vector>
#include"File.h"
#include <algorithm>

using namespace std;

class file;
class folder
{
public:
	string name;
	vector<folder*> folders;
	vector<file*> files;
	folder* parent;
	time_t creation_time;
	string owner;
	string path;
	bool hidden;
public:
	folder(string n = "NULL", string p = "", folder* parent_ = nullptr, vector<file*> fs = vector<file*>(), vector<folder*> Fs = vector<folder*>()) : name(n), folders(Fs), files(fs), hidden(false), path(p), parent(parent_)
	{

	}
	void remove_file(string name)
	{
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i]->name == name)
			{
				swap(files[i], files[files.size() - 1]);
				files.pop_back();
			}
		}

	}
	void remove_folder(string name)
	{
		for (int i = 0; i < folders.size(); i++)
		{
			if (folders[i]->name == name)
			{
				swap(folders[i], folders[folders.size() - 1]);
				folders.pop_back();
			}
		}

	}
	void emptydir()
	{
		files.resize(0);
		folders.resize(0);
	}
	folder* FindFolder(string name)
	{
		for (int i = 0; i < folders.size(); i++)
		{
			if (folders[i]->name == name)
			{
				return folders[i];
			}
		}
		return nullptr;
	}
	file* FindFile(std::string name)
	{
		for (int i = 0; i < files.size(); i++)
		{
			if (files[i]->name == name)
			{
				return files[i];
			}
		}
		return nullptr;
	}
	void insertfile(file* f)
	{
		files.push_back(f);
	}
	void insertfolder(folder* f)
	{
		folders.push_back(f);
	}
	void print()
	{
		cout << " Directory of " << path << "\\" << name << endl << endl;
		for (int i = 0; i < folders.size(); i++)
		{
			cout << "               <DIR>          " << folders[i]->name << endl;

		}
		for (int i = 0; i < files.size(); i++)
		{
			cout << "            " << files[i]->name << endl;
		}
	}
};