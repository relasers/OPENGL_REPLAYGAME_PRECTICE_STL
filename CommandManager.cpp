#pragma once
#include "stdafx.h"
#include "CommandManager.h"




CCommand::CCommand()
{
}

CCommand::~CCommand()
{
}

CCommandManager::CCommandManager()
{

}


CCommandManager::~CCommandManager()
{
}

void CCommandManager::InsertCommand(CCommand::CommandPack commandpack)
{
	switch (commandpack.commandtype) {
	case CCommand::CommandType::KeyBoardType:
		m_pKeycommandlist.push_back(new CCommand(commandpack));
		break;
	case CCommand::CommandType::MouseMove:
		m_pMouseMovecommandlist.push_back(new CCommand(commandpack));
		break;
	case CCommand::CommandType::MouseShoot:
		m_pMouseShootcommandlist.push_back(new CCommand(commandpack));
		break;
	default:
		break;
	}
}

bool CCommandManager::CheckExecutableMouseMoveCommand(double timeelapesd)
{
	if (!(mouse_move_iter != m_pMouseMovecommandlist.end())) return false;
	CCommand* command = new CCommand(*(mouse_move_iter));
	if (command->GetCommand().timeElapsed > timeelapesd) return false;
	delete command;
	return true;
}

bool CCommandManager::CheckExecutableMouseShootCommand(double timeelapesd)
{
	if (!(mouse_shoot_iter != m_pMouseShootcommandlist.end())) return false;
	CCommand* command = new CCommand(*(mouse_shoot_iter));
	if (command->GetCommand().timeElapsed > timeelapesd) return false;
	delete command;
	return true;
}

bool CCommandManager::CheckExecutablaKeyboardCommand(double timeelapesd)
{
	if (!(key_iter != m_pKeycommandlist.end())) return false;
	CCommand* command = new CCommand(*(key_iter));
	if (command->GetCommand().timeElapsed > timeelapesd) return false;
	delete command;
	return true;
}

CCommand* CCommandManager::ExecuteKeyCommand()
{
	CCommand* command = new CCommand(*(key_iter));
	key_iter++;
	return command;
}

CCommand* CCommandManager::ExecuteMouseMoveCommand()
{
	CCommand* command = new CCommand(*(mouse_move_iter));
	mouse_move_iter++;
	return command;
}

CCommand* CCommandManager::ExecuteMouseShootCommand()
{
	CCommand* command = new CCommand(*(mouse_shoot_iter));
	mouse_shoot_iter++;
	return command;
}

void CCommandManager::Initialize()
{
	m_pKeycommandlist.clear();
	m_pMouseMovecommandlist.clear();
	m_pMouseShootcommandlist.clear();

	m_pKeycommandlist.reserve(10000);
	m_pMouseMovecommandlist.reserve(10000);
	m_pMouseShootcommandlist.reserve(10000);
	
	key_iter = m_pKeycommandlist.begin();
	mouse_move_iter = m_pMouseMovecommandlist.begin();
	mouse_shoot_iter = m_pMouseShootcommandlist.begin();

}


void CCommandManager::SaveCommand()
{
	HWND consoleWindowHandle = GetConsoleWindow();
	SetWindowPos(
		consoleWindowHandle,
		HWND_TOPMOST, 
		0, 0,
		0, 0, 
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW 
	);
	ShowWindow(consoleWindowHandle, SW_NORMAL);

	string filename;

	cout << "저장할 파일의 이름을 입력하시오" << endl << " ( 확장자 X ), ex > commandlist" << endl;
	cout << " :: ";
	cin >> filename;
	
	filename.append(".save");



	ofstream out(filename, std::ios::out | std::ios::binary);
	
	for (auto& p : m_pKeycommandlist) {
		out << (int)(p->GetCommand().commandtype) << '\t'
			<< p->GetCommand().lParam << '\t'
			<< p->GetCommand().bFront << '\t'
			<< p->GetCommand().bBack << '\t'
			<< p->GetCommand().bLeft << '\t'
			<< p->GetCommand().bRight << '\t'
			<< p->GetCommand().bswitched << '\t'
			<< p->GetCommand().timeElapsed
			<< endl;
	}
	for (auto& p : m_pMouseMovecommandlist) {
		out << (int)(p->GetCommand().commandtype) << '\t'
			<< p->GetCommand().lParam << '\t'
			<< p->GetCommand().bFront << '\t'
			<< p->GetCommand().bBack << '\t'
			<< p->GetCommand().bLeft << '\t'
			<< p->GetCommand().bRight << '\t'
			<< p->GetCommand().bswitched << '\t'
			<< p->GetCommand().timeElapsed
			<< endl;
	}
	for (auto& p : m_pMouseShootcommandlist) {
		out << (int)(p->GetCommand().commandtype) << '\t'
			<< p->GetCommand().lParam << '\t'
			<< p->GetCommand().bFront << '\t'
			<< p->GetCommand().bBack << '\t'
			<< p->GetCommand().bLeft << '\t'
			<< p->GetCommand().bRight << '\t'
			<< p->GetCommand().bswitched << '\t'
			<< p->GetCommand().timeElapsed
			<< endl;
	}

	cout << " 저장 완료했습니다. " << endl;
}

void CCommandManager::LoadCommand()
{
	HWND consoleWindowHandle = GetConsoleWindow();
	SetWindowPos(
		consoleWindowHandle,
		HWND_TOPMOST,
		0, 0,
		0, 0,
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW
	);
	ShowWindow(consoleWindowHandle,SW_NORMAL);

	m_pKeycommandlist.clear();
	m_pMouseMovecommandlist.clear();
	m_pMouseShootcommandlist.clear();

	bool read_complete = false;

	while (!read_complete)
	{

		

		string filename;

		cout << "불러올 파일의 이름을 입력하시오" << endl << " ( 확장자 X ), ex > commandlist" << endl;
		cout << " :: ";
		cin >> filename;

		filename.append(".save");
		ifstream in(filename);



		if (in.is_open()) {

			read_complete = true;

			while (!in.eof()) {

				CCommand::CommandPack commandpack;
				unsigned int commandtype = 0;

				in >> commandtype >>
					commandpack.lParam >>
					commandpack.bFront >>
					commandpack.bBack >>
					commandpack.bLeft >>
					commandpack.bRight >>
					commandpack.bswitched >>
					commandpack.timeElapsed;

				commandpack.commandtype = static_cast<CCommand::CommandType>(commandtype);

				switch (commandpack.commandtype) {

				case CCommand::CommandType::KeyBoardType:
					m_pKeycommandlist.push_back(new CCommand(commandpack));
					break;
				case CCommand::CommandType::MouseMove:
					m_pMouseMovecommandlist.push_back(new CCommand(commandpack));
					break;
				case CCommand::CommandType::MouseShoot:
					m_pMouseShootcommandlist.push_back(new CCommand(commandpack));
					break;
				default:
					break;
				}
			}
		}

		if (!read_complete) cout << "파일을 불러오는데 실패했습니다. " << endl;
	}
	

	key_iter = m_pKeycommandlist.begin();
	mouse_move_iter = m_pMouseMovecommandlist.begin();
	mouse_shoot_iter = m_pMouseShootcommandlist.begin();

}
