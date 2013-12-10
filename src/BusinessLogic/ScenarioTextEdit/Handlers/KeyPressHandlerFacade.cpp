#include "KeyPressHandlerFacade.h"

#include "PrepareHandler.h"
#include "PreHandler.h"
#include "SceneHeaderHandler.h"
#include "ActionHandler.h"
#include "CharacterHandler.h"
#include "ParentheticalHandler.h"
#include "DialogHandler.h"

#include <BusinessLogic/ScenarioTextEdit/ScenarioTextEdit.h>

#include <QTextBlock>
#include <QKeyEvent>

using namespace KeyProcessingLayer;


void KeyPressHandlerFacade::prepare(QKeyEvent* _event)
{
	m_prepareHandler->handle(_event);
}

void KeyPressHandlerFacade::prehandle(QKeyEvent* _event)
{
	m_preHandler->handle(_event);
}

void KeyPressHandlerFacade::handle(QKeyEvent* _event)
{
	//
	// FIXME: вставка, копирование, вырезание,
	//		  отмена, повтор
	//

	QTextBlock currentBlock = m_editor->textCursor().block();
	ScenarioTextBlockStyle::Type currentType = m_editor->scenarioBlockType(currentBlock);
	AbstractKeyHandler* currentHandler = handlerFor(currentType);

	//
	// Если удалось получить обработчик выполним предназначенные ему действия
	//
	if (currentHandler != 0) {
		currentHandler->handle(_event);
	}
}

bool KeyPressHandlerFacade::needSendEventToBaseClass() const
{
	return m_prepareHandler->needSendEventToBaseClass();
}

// ******** private ********

KeyPressHandlerFacade::KeyPressHandlerFacade(ScenarioTextEdit* _editor) :
	m_editor(_editor)
{
	m_prepareHandler = new PrepareHandler(_editor);
	m_preHandler = new PreHandler(_editor);
	m_sceneHeaderHandler = new SceneHeaderHandler(_editor);
	m_actionHandler = new ActionHandler(_editor);
	m_characterHandler = new CharacterHandler(_editor);
	m_parentheticalHandler = new ParentheticalHandler(_editor);
	m_dialogHandler = new DialogHandler(_editor);
}

AbstractKeyHandler* KeyPressHandlerFacade::handlerFor(ScenarioTextBlockStyle::Type _type)
{
	AbstractKeyHandler* handler = 0;

	switch (_type) {
		case ScenarioTextBlockStyle::SceneHeader: {
			handler = m_sceneHeaderHandler;
			break;
		}

		case ScenarioTextBlockStyle::Action: {
			handler = m_actionHandler;
			break;
		}

		case ScenarioTextBlockStyle::Character: {
			handler = m_characterHandler;
			break;
		}
		case ScenarioTextBlockStyle::Parenthetical: {
			handler = m_parentheticalHandler;
			break;
		}

		case ScenarioTextBlockStyle::Dialog: {
			handler = m_dialogHandler;
			break;
		}

		case ScenarioTextBlockStyle::Transition: break;
		case ScenarioTextBlockStyle::NoteText: break;
		case ScenarioTextBlockStyle::TitleHeader: break;
		case ScenarioTextBlockStyle::Title: break;
		case ScenarioTextBlockStyle::SceneGroupHeader: break;
		case ScenarioTextBlockStyle::SceneGroupFooter: break;
		case ScenarioTextBlockStyle::SimpleText: break;
		default: break;
	}

	return handler;
}

// ********
// Реализация одиночки

KeyPressHandlerFacade* KeyPressHandlerFacade::instance(ScenarioTextEdit* _editor)
{
	//
	// Если необходимо:
	// ... инициилизируем обработчик
	// ... устанавливаем обработчику текстовый редактор
	//
	if (s_instance == 0) {
		s_instance = new KeyPressHandlerFacade(_editor);
	}

	if (s_instance->m_editor != _editor) {
		Q_ASSERT_X(0, Q_FUNC_INFO, "Can't reinitialize KeyPressHandlerFacade");
	}

	return s_instance;
}

KeyPressHandlerFacade* KeyPressHandlerFacade::s_instance = 0;

// ********