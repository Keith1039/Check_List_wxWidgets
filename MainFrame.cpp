#include "MainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
	fileName = "Check.txt";
	wxPanel* panel = new wxPanel(this);  // creates a panel that covers the screen

	wxStaticText* panelTitle = new wxStaticText(panel, wxID_ANY, "TO-DO List", wxPoint(0, 50), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	// make the text bold
	wxFont font = panelTitle->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	// scale up the font
	panelTitle->SetFont(font);
	panelTitle->SetFont(panelTitle->GetFont().Scale(2));  // scale up the font size
	// make text control
	textControl = new wxTextCtrl(panel, wxID_ANY, "editable text", wxPoint(100, 100), wxSize(500, -1), wxTE_PROCESS_ENTER);
	// make the add button
	wxButton* addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(605, 100), wxSize(75, -1));

	//make the list box and allow for multiple checks
	list = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 130), wxSize(580, 400));

	// clear button
	wxButton* clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(100, 530), wxSize(75, -1));

	InitFromFile(fileName);  // get the information from a text file

	addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAddEvent, this);
	clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearEvent, this);
	textControl->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnAddEvent, this);
	list->Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyDownEvent, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnExit, this);
}

void MainFrame::OnAddEvent(wxCommandEvent& evt) {
	AddValue();
}

void MainFrame::OnClearEvent(wxCommandEvent& evt) {

	wxMessageDialog dialogue(this, "Are you sure you want to clear all tasks?", "Clear", wxYES_NO | wxCANCEL);
	int result = dialogue.ShowModal();
	if (result == wxID_YES) {
		MainFrame::list->Clear();  // removes everything in the list
	}

}

void MainFrame::OnExit(wxCloseEvent& evt) {
	LoadToFile(MainFrame::fileName);  // save the current data into a file
	evt.Skip();  // allow the event to propogate upwards
}

void MainFrame::OnKeyDownEvent(wxKeyEvent& evt) {
	switch (evt.GetKeyCode()) {
	case WXK_DELETE:
		DeleteSelectedTask();
		break;
	}
	evt.Skip(); // let another handler receive the event
}


void MainFrame::AddValue() {
	wxString str = MainFrame::textControl->GetValue(); // extract the string
	if (str != "") {
		list->Insert(str, list->GetCount());  // insert the string after the previous one
		MainFrame::textControl->Clear(); // clear the text control
	}
	textControl->SetFocus();  // allows user to continue typing after adding
}

void MainFrame::InitFromFile(std::string fileName)
{
	MainFrame::vectorList = loadTasksFromFile(fileName);
	for (const Task& task : MainFrame::vectorList) {
		int index = list->GetCount();
		list->Insert(task.description, index);
		list->Check(index, task.done); // check the box 
	}
}

void MainFrame::LoadToFile(std::string fileName)
{
	ListToVectorList();
	saveTasksToFile(MainFrame::vectorList, fileName);  // saves the tasks to a file
}

void MainFrame::DeleteSelectedTask()
{
	int selection = MainFrame::list->GetSelection();
	// if no selection was made do nothing
	if (selection == wxNOT_FOUND) {
		return;
	}
	list->Delete(selection);  // if there was a selection delete it
	if (selection != 0) {
		list->Select(selection - 1);
	}
}

void MainFrame::ListToVectorList() {
	std::string description;
	bool done;
	vectorList.clear();  // ensure that the vector list is empty
	// iterate through checkbox list and add the struct to vector list
	for (int i = 0; i < list->GetCount(); i++) {
		description = list->GetString(i).ToStdString();
		done = list->IsChecked(i);
		vectorList.push_back(Task{ description, done });
	}
}
void MainFrame::SwapTasks(int i, int j)
{
}

