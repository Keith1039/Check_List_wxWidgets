#pragma once
#include <wx/wx.h>
#include "Task.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	std::string fileName;
	std::vector<Task> vectorList;
	wxTextCtrl* textControl;
	wxCheckListBox* list;

	void OnAddEvent(wxCommandEvent& evt);
	void OnClearEvent(wxCommandEvent& evt);
	void OnExit(wxCloseEvent& evt);
	void OnKeyDownEvent(wxKeyEvent& evt);
	void AddValue();
	void InitFromFile(std::string fileName);
	void LoadToFile(std::string fileName);
	void DeleteSelectedTask();
	void ListToVectorList();
	void SwapTasks(int i, int j);
};

