#pragma once
#include "stdafx.h"
#include <list>

class CCommand
{
public:

	enum class CommandType : int {
		None = 0
		, KeyBoardType
		, MouseMove
		, MouseShoot
		,Count
	};

	struct CommandPack {
		CommandType commandtype;

		LPARAM					lParam;

		bool					bFront;
		bool					bBack;
		bool					bLeft;
		bool					bRight;

		bool					bswitched; // 마우스클릭, 부스터 키 명령어
		
		double timeElapsed;

	};

private:
	CommandPack m_commandpack;
public:
	CCommand();
	CCommand(CommandPack commandpack) {
		m_commandpack = commandpack;
	};
	CCommand(CCommand* command) {
		m_commandpack = command->GetCommand();
	};
	~CCommand();

	CommandPack GetCommand() {
		return m_commandpack;
	}

};


class CCommandManager
{
public:

	enum class CommandMode : int {
		None = 0
		, GamePlay
		, GameReplay
		, Count
	};


	

private:

	std::vector<CCommand*>	m_pKeycommandlist;
	std::vector<CCommand*>	m_pMouseMovecommandlist;
	std::vector<CCommand*>	m_pMouseShootcommandlist;

	std::vector<CCommand*>::iterator key_iter;
	std::vector<CCommand*>::iterator mouse_move_iter;
	std::vector<CCommand*>::iterator mouse_shoot_iter;

	CommandMode				m_commandmode;
	CCommand::CommandPack	m_commandpack;

public:
	CCommandManager();
	~CCommandManager();

	CommandMode GetCommandMode() { return m_commandmode; }
	void SetCommandMode(CommandMode mode) {
		m_commandmode = mode;
	}

	void InsertCommand(CCommand::CommandPack commandpack);

	bool CheckExecutableMouseMoveCommand(double timeelapesd);
	bool CheckExecutableMouseShootCommand(double timeelapesd);
	bool CheckExecutablaKeyboardCommand(double timeelapesd);


	CCommand* ExecuteKeyCommand();
	CCommand* ExecuteMouseMoveCommand();
	CCommand* ExecuteMouseShootCommand();

	void Initialize();

	void SaveCommand();
	void LoadCommand();
};

